/*
 * This file contains software that has been made available under
 * The Mozilla Public License 1.1. Use and distribution hereof are
 * subject to the restrictions set forth therein.
 *
 * Copyright (c) 2003 TADA AB - Taby Sweden
 * All Rights Reserved
 */
#include "pljava/type/Type_priv.h"

static Type      s_Oid;
static TypeClass s_OidClass;
static jclass    s_Oid_class;
static jmethodID s_Oid_init;
static jfieldID  s_Oid_m_native;
static jfieldID  s_Oid_s_invalidOid;

/*
 * org.postgresql.pljava.type.Oid type.
 */
static jvalue _Oid_coerceDatum(Type self, JNIEnv* env, Datum arg)
{
	jvalue result;
	Oid oid = DatumGetObjectId(arg);
	if(OidIsValid(oid))
		result.l = (*env)->NewObject(env, s_Oid_class, s_Oid_init, DatumGetObjectId(arg));
	else
		result.l = (*env)->GetStaticObjectField(env, s_Oid_class, s_Oid_s_invalidOid);
	return result;
}

static Datum _Oid_coerceObject(Type self, JNIEnv* env, jobject oidObj)
{
	return ObjectIdGetDatum((*env)->GetIntField(env, oidObj, s_Oid_m_native));
}

static Type Oid_obtain(Oid typeId)
{
	return s_Oid;
}

/* Make this datatype available to the postgres system.
 */
extern Datum Oid_initialize(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(Oid_initialize);
Datum Oid_initialize(PG_FUNCTION_ARGS)
{
	JNIEnv* env = (JNIEnv*)PG_GETARG_POINTER(0);

	s_Oid_class = (*env)->NewGlobalRef(
				env, PgObject_getJavaClass(env, "org/postgresql/pljava/Oid"));

	s_Oid_init = PgObject_getJavaMethod(
				env, s_Oid_class, "<init>", "(I)V");

	s_Oid_m_native = PgObject_getJavaField(
				env, s_Oid_class, "m_native", "I");

	s_Oid_s_invalidOid = PgObject_getStaticJavaField(
				env, s_Oid_class, "s_invalidOid", "Lorg/postgresql/pljava/Oid;");

	s_OidClass = TypeClass_alloc("type.Oid");
	s_OidClass->JNISignature   = "Lorg/postgresql/pljava/Oid;";
	s_OidClass->javaTypeName   = "org.postgresql.pljava.Oid";
	s_OidClass->coerceDatum    = _Oid_coerceDatum;
	s_OidClass->coerceObject   = _Oid_coerceObject;
	s_Oid = TypeClass_allocInstance(s_OidClass);

	Type_registerPgType(OIDOID, Oid_obtain);
	Type_registerJavaType("org.postgresql.pljava.Oid", Oid_obtain);
	PG_RETURN_VOID();
}
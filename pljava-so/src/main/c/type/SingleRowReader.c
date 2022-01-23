/*
 * Copyright (c) 2004-2022 Tada AB and other contributors, as listed below.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the The BSD 3-Clause License
 * which accompanies this distribution, and is available at
 * http://opensource.org/licenses/BSD-3-Clause
 *
 * Contributors:
 *   Tada AB
 *   PostgreSQL Global Development Group
 *   Chapman Flack
 *
 * @author Thomas Hallgren
 */
#include "pljava/type/Type_priv.h"
#include "pljava/type/SingleRowReader.h"

#include <executor/executor.h>
#include <executor/spi.h>
#include <utils/typcache.h>

#include "pljava/DualState.h"
#include "pljava/Exception.h"
#include "pljava/Invocation.h"
#include "pljava/type/TupleDesc.h"

#include "org_postgresql_pljava_jdbc_SingleRowReader.h"

static jclass s_SingleRowReader_class;
static jmethodID s_SingleRowReader_init;

jobject pljava_SingleRowReader_getTupleDesc(HeapTupleHeader ht)
{
	jobject result;
	TupleDesc tupleDesc =
	  lookup_rowtype_tupdesc(HeapTupleHeaderGetTypeId(ht),
				 HeapTupleHeaderGetTypMod(ht));
	result = pljava_TupleDesc_create(tupleDesc);
	/*
	 * pljava_TupleDesc_create() creates a copy of the tuple descriptor, so
	 * can release this now
	 */
	ReleaseTupleDesc(tupleDesc);
	return result;
}

jobject pljava_SingleRowReader_create(HeapTupleHeader ht)
{
	Ptr2Long p2lht;
	jobject result;
	jobject jtd = pljava_SingleRowReader_getTupleDesc(ht);

	p2lht.longVal = 0L;

	p2lht.ptrVal = ht;

	result =
		JNI_newObjectLocked(s_SingleRowReader_class, s_SingleRowReader_init,
			p2lht.longVal, jtd);

	JNI_deleteLocalRef(jtd);
	return result;
}

/* Make this datatype available to the postgres system.
 */
void pljava_SingleRowReader_initialize(void)
{
	JNINativeMethod methods[] =
	{
		{
		"_getObject",
		"(JJILjava/lang/Class;)Ljava/lang/Object;",
	  	Java_org_postgresql_pljava_jdbc_SingleRowReader__1getObject
		},
		{ 0, 0, 0 }
	};
	jclass cls =
		PgObject_getJavaClass("org/postgresql/pljava/jdbc/SingleRowReader");
	PgObject_registerNatives2(cls, methods);
	s_SingleRowReader_init = PgObject_getJavaMethod(cls, "<init>",
		"(JLorg/postgresql/pljava/internal/TupleDesc;)V");
	s_SingleRowReader_class = JNI_newGlobalRef(cls);
	JNI_deleteLocalRef(cls);
}


/****************************************
 * JNI methods
 ****************************************/

/*
 * Class:     org_postgresql_pljava_jdbc_SingleRowReader
 * Method:    _getObject
 * Signature: (JJILjava/lang/Class;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL
Java_org_postgresql_pljava_jdbc_SingleRowReader__1getObject(JNIEnv* env, jclass clazz, jlong hth, jlong jtd, jint attrNo, jclass rqcls)
{
	jobject result = 0;
	if(hth != 0 && jtd != 0)
	{
		Ptr2Long p2lhth;
		Ptr2Long p2ltd;
		p2lhth.longVal = hth;
		p2ltd.longVal = jtd;
		BEGIN_NATIVE
		PG_TRY();
		{
			Type type = pljava_TupleDesc_getColumnType(
				(TupleDesc) p2ltd.ptrVal, (int) attrNo);
			if (type != 0)
			{
				Datum binVal;
				bool wasNull = false;
				binVal = GetAttributeByNum(
							(HeapTupleHeader)p2lhth.ptrVal,
							(AttrNumber)attrNo, &wasNull);
				if(!wasNull)
					result = Type_coerceDatumAs(type, binVal, rqcls).l;
			}
		}
		PG_CATCH();
		{
			Exception_throw_ERROR("GetAttributeByNum");
		}
		PG_END_TRY();
		END_NATIVE
	}
	return result;
}

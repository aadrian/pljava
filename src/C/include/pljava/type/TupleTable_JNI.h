/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_postgresql_pljava_internal_TupleTable */

#ifndef _Included_org_postgresql_pljava_internal_TupleTable
#define _Included_org_postgresql_pljava_internal_TupleTable
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_postgresql_pljava_internal_TupleTable
 * Method:    getCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_postgresql_pljava_internal_TupleTable_getCount
  (JNIEnv *, jobject);

/*
 * Class:     org_postgresql_pljava_internal_TupleTable
 * Method:    getSlot
 * Signature: (I)Lorg/postgresql/pljava/internal/TupleTableSlot;
 */
JNIEXPORT jobject JNICALL Java_org_postgresql_pljava_internal_TupleTable_getSlot
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif

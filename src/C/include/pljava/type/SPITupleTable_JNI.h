/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_postgresql_pljava_internal_SPITupleTable */

#ifndef _Included_org_postgresql_pljava_internal_SPITupleTable
#define _Included_org_postgresql_pljava_internal_SPITupleTable
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_postgresql_pljava_internal_SPITupleTable
 * Method:    getCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_postgresql_pljava_internal_SPITupleTable_getCount
  (JNIEnv *, jobject);

/*
 * Class:     org_postgresql_pljava_internal_SPITupleTable
 * Method:    getSlot
 * Signature: (I)Lorg/postgresql/pljava/internal/Tuple;
 */
JNIEXPORT jobject JNICALL Java_org_postgresql_pljava_internal_SPITupleTable_getSlot
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_postgresql_pljava_internal_SPITupleTable
 * Method:    getTupleDesc
 * Signature: ()Lorg/postgresql/pljava/internal/TupleDesc;
 */
JNIEXPORT jobject JNICALL Java_org_postgresql_pljava_internal_SPITupleTable_getTupleDesc
  (JNIEnv *, jobject);

/*
 * Class:     org_postgresql_pljava_internal_SPITupleTable
 * Method:    invalidate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_postgresql_pljava_internal_SPITupleTable_invalidate
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif

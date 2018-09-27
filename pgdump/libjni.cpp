//
// Created by giacomo on 23/09/18.
//

#define IS_LIBRARY
#include "libjni_test.cpp"
#include "../fromJava/org_ufl_hypogator_jackb_traversers_conceptnet_JNIEntryPoint.h"

JNIEXPORT void JNICALL Java_org_ufl_hypogator_jackb_traversers_conceptnet_JNIEntryPoint_init(JNIEnv * env, jobject obj)
{
    initializeRelationships();
    graph.open();
}

JNIEXPORT void JNICALL Java_org_ufl_hypogator_jackb_traversers_conceptnet_JNIEntryPoint_dispose(JNIEnv * env, jobject obj)
{
    graph.clos();
}

using safe_long = uint64_t;

JNIEXPORT jobjectArray JNICALL Java_org_ufl_hypogator_jackb_traversers_conceptnet_JNIEntryPoint_pgObjectOut
        (JNIEnv * env, jobject obj, jlong offset, jboolean ingoing, jlong relmap) {
    header *v = vertex_offset(graph.begin, offset);
    LONG_NUMERIC n = ingoing ? vertex_ingoing_edges_len(v) : vertex_outgoing_edges_len(v);
    edges_in_vertices* vec = ingoing ? vertex_ingoing_edges_vec(v) : vertex_outgoing_edges_vec(v);
    char** toRet = NULL;
    unsigned long toretSize = 0;
    for (LONG_NUMERIC i = 0; i<n; i++) {
        if (vec[i].edgeHash & relmap) {
            toretSize++;
            toRet = (char**)realloc(toRet, toretSize * sizeof (char *));
            toRet[toretSize-1] = graph.resolveEdgeValue(vec[i].edgeId);
        }
    }
    jobjectArray realRet = env->NewObjectArray(static_cast<jsize>(toretSize), env->FindClass("java/lang/String"),
                                               nullptr);
    for (unsigned long i = 0; i<toretSize; i++) {
        jstring str = env->NewStringUTF(toRet[i]);
        env->SetObjectArrayElement(realRet,i,str);
    }
    return realRet;
}
//
// Created by giacomo on 26/09/18.
//

#include "libfuzzymatch.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <unordered_set>

#include "org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI.h"
std::string baseDir;
std::unordered_map<std::string, FuzzyMatch_FDContainer> map;
extern std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> fmatch_converter;

std::string jstring2atring(JNIEnv *env, jstring jStr) {
    const char* benedict = env->GetStringUTFChars(jStr, NULL);
    std::string strMixed = std::string(benedict);
    std::wstring wide = fmatch_converter.from_bytes(strMixed.c_str());
    std::string str = fmatch_converter.to_bytes(wide);
    env->ReleaseStringUTFChars(jStr, benedict);
    return str;
}

JNIEXPORT void JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_openDirectory
        (JNIEnv * env, jobject self, jstring str) {
    baseDir = jstring2atring(env, str);
    if (baseDir[baseDir.size()-1] != '/') {
        baseDir += "/";
    }
}

JNIEXPORT void JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_openDimensioN
        (JNIEnv * env, jobject self, jstring dim) {
    std::string dimension = jstring2atring(env, dim);
    map[dimension].open(baseDir+dimension+"_csvDir");
}

JNIEXPORT void JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_fuzzyMatch
        (JNIEnv * env, jobject self, jstring dim, jdouble threshold, jint topk, jstring term) {
    // openDimension
    std::string dimension = jstring2atring(env, dim);
    map[dimension].open(baseDir+dimension+"_csvDir");

    // fuzzyMatch
    std::string term2 = jstring2atring(env, term);
    map[dimension].fuzzyMatch(threshold, topk, term2);
}

JNIEXPORT jboolean JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_hasCurrent
        (JNIEnv * env, jobject self, jstring dim) {
    std::string dimension = jstring2atring(env, dim);
    return static_cast<jboolean>(map[dimension].hasCurrent());
}

JNIEXPORT void JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_closeDimension
        (JNIEnv *env, jobject self, jstring dim) {
    std::string dimension = jstring2atring(env, dim);
    map.erase(dimension);
}

JNIEXPORT jdouble JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_getCurrentKey
        (JNIEnv * env, jobject self, jstring dim) {
    std::string dimension = jstring2atring(env, dim);
    return map[dimension].getCurrentKey();
}

JNIEXPORT jlong JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_getCurrentValue
        (JNIEnv * env, jobject self, jstring dim) {
    std::string dimension = jstring2atring(env, dim);
    return map[dimension].getCurrentValue();
}

JNIEXPORT jboolean JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_next
        (JNIEnv * env, jobject self, jstring dim) {
    std::string dimension = jstring2atring(env, dim);
    return static_cast<jboolean>(map[dimension].next());
}

JNIEXPORT void JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_closeDirectory
        (JNIEnv * env, jobject self) {
    map.clear();
}


JNIEXPORT jlongArray JNICALL Java_org_ufl_hypogator_jackb_fuzzymatching_TwoGramIndexerJNI_containsExactTerm
        (JNIEnv * env, jobject self, jstring dim, jstring t) {
    std::string dimension = jstring2atring(env, dim);
    std::string term      = jstring2atring(env, t);
    void* gramPtr = map[dimension].termToObjects.searchForId(term);
    if (gramPtr != nullptr) {
        LONG_NUMERIC    n = LONG_ARRAY_SIZE(gramPtr);
        LONG_NUMERIC* ptr = LONG_ARRAY_ELEMENT(gramPtr);
        jlongArray toret = env->NewLongArray(static_cast<jsize>(n));
        env->SetLongArrayRegion(toret, 0, static_cast<jsize>(n), reinterpret_cast<const jlong *>(ptr));
        return toret;
    } else {
        return env->NewLongArray(0);
    }
}

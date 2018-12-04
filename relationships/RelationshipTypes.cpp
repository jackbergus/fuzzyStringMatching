//
// Created by giacomo on 04/12/18.
//

#include "RelationshipTypes.h"

const std::map<unsigned long, unsigned long> inversionMap = {
        {HT_NONE, HT_NONE},
        {HT_EQ, HT_EQ},
        {HT_RELATEDTO, HT_RELATEDTO},
        {HT_HAS_CONTENT_INSTANCE, HT_PARTOF},
        {HT_PARTOF, HT_HAS_CONTENT_INSTANCE},
        {HT_RIGHT_TO_LEFT_IMPL, HT_LEFT_TO_RIGHT_IMPL},
        {HT_LEFT_TO_RIGHT_IMPL, HT_RIGHT_TO_LEFT_IMPL}
};

const std::map<std::string, unsigned long> enumMap = {
        {"Antonym", 2L},
        {"AtLocation", 4L},
        {"CapableOf", 8L},
        {"Causes", 16L},
        {"CausesDesire", 32L},
        {"CreatedBy", 64L},
        {"DefinedAs", 128L},
        {"DerivedFrom", 256L},
        {"Desires", 512L},
        {"DistinctFrom", 1024L},
        {"Entails", 2048L},
        {"EtymologicallyDerivedFrom", 4096L},
        {"EtymologicallyRelatedTo", 8192L},
        {"ExternalURL", 16384L},
        {"FormOf", 32768L},
        {"HasA", 65536L},
        {"HasContext", 131072L},
        {"HasFirstSubevent", 262144L},
        {"HasLastSubevent", 524288L},
        {"HasPrerequisite", 1048576L},
        {"HasProperty", 2097152L},
        {"HasSubevent", 4194304L},
        {"InstanceOf", 8388608L},
        {"IsA", 16777216L},
        {"LocatedNear", 33554432L},
        {"MadeOf", 67108864L},
        {"MannerOf", 134217728L},
        {"MotivatedByGoal", 268435456},
        {"NotCapableOf", 536870912L},
        {"NotDesires", 1073741824L},
        {"NotHasProperty", 2147483648L},
        {"NotUsedFor", 4294967296L},
        {"ObstructedBy", 8589934592L},
        {"PartOf", 17179869184L},
        {"ReceivesAction", 34359738368L},
        {"RelatedTo", 68719476736L},
        {"SimilarTo", 137438953472L},
        {"SymbolOf", 274877906944L},
        {"Synonym", 549755813888L},
        {"UsedFor", 1099511627776L},
        {"capital", 2199023255552L},
        {"field", 4398046511104L},
        {"genre", 8796093022208L},
        {"genus", 17592186044416L},
        {"influencedBy", 35184372088832L},
        {"knownFor", 70368744177664L},
        {"language", 140737488355328L},
        {"leader", 281474976710656L},
        {"occupation", 562949953421312L},
        {"product", 1125899906842624L}
};
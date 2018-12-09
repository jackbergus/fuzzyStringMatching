//
// Created by giacomo on 04/12/18.
//

#ifndef INCONSISTENCY_RELATIONSHIPTYPES_H
#define INCONSISTENCY_RELATIONSHIPTYPES_H

#include  <map>

enum RelationshipTypes: unsigned long {
    Antonym = 2L,
    AtLocation = 4L,
    CapableOf = 8L,
    Causes = 16L,
    CausesDesire = 32L,
    CreatedBy = 64L,
    DefinedAs = 128L,
    DerivedFrom = 256L,
    Desires = 512L,
    DistinctFrom = 1024L,
    Entails = 2048L,
    EtymologicallyDerivedFrom = 4096L,
    EtymologicallyRelatedTo = 8192L,
    ExternalURL = 16384L,
    FormOf = 32768L,
    HasA = 65536L,
    HasContext = 131072L,
    HasFirstSubevent = 262144L,
    HasLastSubevent = 524288L,
    HasPrerequisite = 1048576L,
    HasProperty = 2097152L,
    HasSubevent = 4194304L,
    InstanceOf = 8388608L,
    IsA = 16777216L,
    LocatedNear = 33554432L,
    MadeOf = 67108864L,
    MannerOf = 134217728L,
    MotivatedByGoal = 268435456,
    NotCapableOf = 536870912L,
    NotDesires = 1073741824L,
    NotHasProperty = 2147483648L,
    NotUsedFor = 4294967296L,
    ObstructedBy = 8589934592L,
    PartOf = 17179869184L,
    ReceivesAction = 34359738368L,
    RelatedTo = 68719476736L,
    SimilarTo = 137438953472L,
    SymbolOf = 274877906944L,
    Synonym = 549755813888L,
    UsedFor = 1099511627776L,
    capital = 2199023255552L,
    field = 4398046511104L,
    genre = 8796093022208L,
    genus = 17592186044416L,
    influencedBy = 35184372088832L,
    knownFor = 70368744177664L,
    language = 140737488355328L,
    leader = 281474976710656L,
    occupation = 562949953421312L,
    product = 1125899906842624L
};

/**
 * Map associating to each string representation the associated enum value
 */
extern const std::map<std::string, unsigned long> enumMap;


constexpr unsigned long isSuitableForHierarchyTraversing_MAP = (65536L | 131072L | 262144L | 524288L | 68719476736L | 8388608L | 16777216L | 134217728L | 137438953472L | 274877906944L | 549755813888L | 4398046511104L | 8796093022208L | 17592186044416L);
#define isSuitableForHierarchyTraversing(x)     (((unsigned long)x) & (isSuitableForHierarchyTraversing_MAP))

constexpr unsigned long HierarchicalTraverseEdgeType_negativeMAP = (536870912L | 1073741824L | 2147483648L | 4294967296L | 2L | 1024L);
#define SemanticEdge_isNegated(x)                    ((bool)(((unsigned long)x) & (isSuitableForHierarchyTraversing_MAP)))
#define SemanticEdge_isPositive(x)                   (!(SemanticEdge_isNegated(x)))

/**
 *   HIERARCHICAL TRAVERSE REPRESENTATION
 */


/**
 * Relationship types expressing equivalence, either negated or not
 */
constexpr unsigned long HT_EQ = 2L | 1024L | 128L | 549755813888L;
#define CHT_EQ      (HT_EQ)

/**
 * Relationship types expressing partof/isa relationships
 */
constexpr unsigned long HT_PARTOF =
        static_cast<unsigned long>(RelationshipTypes::PartOf) |
        static_cast<unsigned long>(RelationshipTypes::IsA) |
        static_cast<unsigned long>(RelationshipTypes::HasContext) |
        static_cast<unsigned long>(RelationshipTypes::FormOf) |
        static_cast<unsigned long>(RelationshipTypes::InstanceOf) |
        static_cast<unsigned long>(RelationshipTypes::SymbolOf) |
        static_cast<unsigned long>(RelationshipTypes::MannerOf) |
        static_cast<unsigned long>(RelationshipTypes::genre) |
        static_cast<unsigned long>(RelationshipTypes::genus) |
        static_cast<unsigned long>(RelationshipTypes::field) |
        static_cast<unsigned long>(RelationshipTypes::product) |
        static_cast<unsigned long>(RelationshipTypes::occupation) |
        static_cast<unsigned long>(RelationshipTypes::leader);

/**
 * Relationship types expressing relatedness, either negated or not
 */
constexpr unsigned long HT_RELATEDTO =
        static_cast<unsigned long>(RelationshipTypes::AtLocation) |
        static_cast<unsigned long>(RelationshipTypes::CapableOf) |
        static_cast<unsigned long>(RelationshipTypes::LocatedNear) |
        static_cast<unsigned long>(RelationshipTypes::SimilarTo) |
        static_cast<unsigned long>(RelationshipTypes::RelatedTo) |
        static_cast<unsigned long>(RelationshipTypes::NotCapableOf);
#define CHT_SIMILAR         (HT_RELATEDTO)

/**
 * Relationship types expressing left to right implication, either negated or not
 */
constexpr unsigned long HT_LEFT_TO_RIGHT_IMPL =
        static_cast<unsigned long>(RelationshipTypes::Causes) |
        static_cast<unsigned long>(RelationshipTypes::CausesDesire) |
        static_cast<unsigned long>(RelationshipTypes::Desires) |
        static_cast<unsigned long>(RelationshipTypes::HasProperty) |
        static_cast<unsigned long>(RelationshipTypes::MadeOf) |
        static_cast<unsigned long>(RelationshipTypes::Entails) |
        static_cast<unsigned long>(RelationshipTypes::EtymologicallyRelatedTo) |
        static_cast<unsigned long>(RelationshipTypes::DerivedFrom) |
        static_cast<unsigned long>(RelationshipTypes::ObstructedBy) |
        static_cast<unsigned long>(RelationshipTypes::EtymologicallyDerivedFrom) |
        static_cast<unsigned long>(RelationshipTypes::knownFor) |
        static_cast<unsigned long>(RelationshipTypes::HasSubevent) |
        static_cast<unsigned long>(RelationshipTypes::HasFirstSubevent) |
        static_cast<unsigned long>(RelationshipTypes::HasLastSubevent) |
        static_cast<unsigned long>(RelationshipTypes::NotDesires) |
        static_cast<unsigned long>(RelationshipTypes::NotHasProperty);


/**
 * Relationship types expressing partof/isa relationships
 */
constexpr unsigned long HT_HAS_CONTENT_INSTANCE =
        static_cast<unsigned long>(RelationshipTypes::capital) | static_cast<unsigned long>(RelationshipTypes::HasA);



#define CHT_CAUSED_BY       (HT_HAS_CONTENT_INSTANCE | HT_PARTOF)

constexpr unsigned long HT_RIGHT_TO_LEFT_IMPL =
    static_cast<unsigned long>(RelationshipTypes::CreatedBy) |
    static_cast<unsigned long>(RelationshipTypes::HasPrerequisite) |
    static_cast<unsigned long>(RelationshipTypes::influencedBy) |
    static_cast<unsigned long>(RelationshipTypes::ReceivesAction) |
    static_cast<unsigned long>(RelationshipTypes::UsedFor) |
    static_cast<unsigned long>(RelationshipTypes::MotivatedByGoal) |
    static_cast<unsigned long>(RelationshipTypes::NotUsedFor);

/**
 * Relationship types expressing no relationship whatsoever
 */
constexpr unsigned long HT_NONE = 140737488355328L | 16384L;
constexpr unsigned long CHT_NONE = (HT_NONE | HT_RIGHT_TO_LEFT_IMPL | HT_LEFT_TO_RIGHT_IMPL);

/**
 * Association between one element nad its inverse
 */
extern const std::map<unsigned long, unsigned long> inversionMap;


/**
 * Checking whether the element matches a given type (represented by a bitmap) or not
 *
 * boolWasInverted: Checking whether I'm looking for the inverted type or not
 * T:             associated coarsened type I'm looking for (or its inversion)
 * x:             enum value to be checked
 */
#define isA(boolWasInverted, T, x)    (((unsigned long)x) & ((boolWasInverted) ? T : (inversionMap.get(T))))


/**
 * Relationships that are preferred to be visited in ConceptNet
 */
constexpr unsigned long HT_PREFERRED_DIRECTIONS = HT_NONE | HT_RELATEDTO| HT_PARTOF | HT_LEFT_TO_RIGHT_IMPL | HT_EQ;
constexpr unsigned long HT_PREFERRED_INVERTED_DIRECTIONS = HT_NONE | HT_RELATEDTO| HT_PARTOF | HT_RIGHT_TO_LEFT_IMPL | HT_EQ;
#define isPreferredDirection_normal(x)              (((unsigned long)x) & HT_PREFERRED_DIRECTIONS)
#define isPreferredDirection(boolWasInverted, x)    (((unsigned long)x) & ((boolWasInverted) ? HT_PREFERRED_INVERTED_DIRECTIONS : HT_PREFERRED_DIRECTIONS))

/**
 *   COARSER HIERARCHICAL TRAVERSE REPRESENTATION
 */


#endif //INCONSISTENCY_RELATIONSHIPTYPES_H

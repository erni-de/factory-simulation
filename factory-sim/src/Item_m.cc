//
// Generated file, do not edit! Created by opp_msgtool 6.2 from Item.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Item_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(Item)

Item::Item(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

Item::Item(const Item& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Item::~Item()
{
}

Item& Item::operator=(const Item& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Item::copy(const Item& other)
{
    this->counter = other.counter;
    this->isDiscarded_ = other.isDiscarded_;
    this->generationTime = other.generationTime;
    this->startTime = other.startTime;
    this->discardTime = other.discardTime;
    this->productionTime = other.productionTime;
}

void Item::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->counter);
    doParsimPacking(b,this->isDiscarded_);
    doParsimPacking(b,this->generationTime);
    doParsimPacking(b,this->startTime);
    doParsimPacking(b,this->discardTime);
    doParsimPacking(b,this->productionTime);
}

void Item::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->counter);
    doParsimUnpacking(b,this->isDiscarded_);
    doParsimUnpacking(b,this->generationTime);
    doParsimUnpacking(b,this->startTime);
    doParsimUnpacking(b,this->discardTime);
    doParsimUnpacking(b,this->productionTime);
}

void Item::increaseCounter(){
    this->counter = this->counter + 1;
}

int Item::getCounter() const
{
    return this->counter;
}

void Item::setCounter(int counter)
{
    this->counter = counter;
}

bool Item::isDiscarded() const
{
    return this->isDiscarded_;
}

void Item::setIsDiscarded(bool isDiscarded)
{
    this->isDiscarded_ = isDiscarded;
}

double Item::getGenerationTime() const
{
    return this->generationTime;
}

void Item::setGenerationTime(double generationTime)
{
    this->generationTime = generationTime;
}

double Item::getStartTime() const
{
    return this->startTime;
}

void Item::setStartTime(double startTime)
{
    this->startTime = startTime;
}

double Item::getDiscardTime() const
{
    return this->discardTime;
}

void Item::setDiscardTime(double discardTime)
{
    this->discardTime = discardTime;
}

double Item::getProductionTime() const
{
    return this->productionTime;
}

void Item::setProductionTime(double productionTime)
{
    this->productionTime = productionTime;
}

class ItemDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_counter,
        FIELD_isDiscarded,
        FIELD_generationTime,
        FIELD_startTime,
        FIELD_discardTime,
        FIELD_productionTime,
    };
  public:
    ItemDescriptor();
    virtual ~ItemDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ItemDescriptor)

ItemDescriptor::ItemDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(Item)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

ItemDescriptor::~ItemDescriptor()
{
    delete[] propertyNames;
}

bool ItemDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Item *>(obj)!=nullptr;
}

const char **ItemDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ItemDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ItemDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int ItemDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_counter
        FD_ISEDITABLE,    // FIELD_isDiscarded
        FD_ISEDITABLE,    // FIELD_generationTime
        FD_ISEDITABLE,    // FIELD_startTime
        FD_ISEDITABLE,    // FIELD_discardTime
        FD_ISEDITABLE,    // FIELD_productionTime
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *ItemDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "counter",
        "isDiscarded",
        "generationTime",
        "startTime",
        "discardTime",
        "productionTime",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int ItemDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "counter") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "isDiscarded") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "generationTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "startTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "discardTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "productionTime") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *ItemDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_counter
        "bool",    // FIELD_isDiscarded
        "double",    // FIELD_generationTime
        "double",    // FIELD_startTime
        "double",    // FIELD_discardTime
        "double",    // FIELD_productionTime
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **ItemDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ItemDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ItemDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ItemDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Item'", field);
    }
}

const char *ItemDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ItemDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        case FIELD_counter: return long2string(pp->getCounter());
        case FIELD_isDiscarded: return bool2string(pp->isDiscarded());
        case FIELD_generationTime: return double2string(pp->getGenerationTime());
        case FIELD_startTime: return double2string(pp->getStartTime());
        case FIELD_discardTime: return double2string(pp->getDiscardTime());
        case FIELD_productionTime: return double2string(pp->getProductionTime());
        default: return "";
    }
}

void ItemDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        case FIELD_counter: pp->setCounter(string2long(value)); break;
        case FIELD_isDiscarded: pp->setIsDiscarded(string2bool(value)); break;
        case FIELD_generationTime: pp->setGenerationTime(string2double(value)); break;
        case FIELD_startTime: pp->setStartTime(string2double(value)); break;
        case FIELD_discardTime: pp->setDiscardTime(string2double(value)); break;
        case FIELD_productionTime: pp->setProductionTime(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Item'", field);
    }
}

omnetpp::cValue ItemDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        case FIELD_counter: return pp->getCounter();
        case FIELD_isDiscarded: return pp->isDiscarded();
        case FIELD_generationTime: return pp->getGenerationTime();
        case FIELD_startTime: return pp->getStartTime();
        case FIELD_discardTime: return pp->getDiscardTime();
        case FIELD_productionTime: return pp->getProductionTime();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Item' as cValue -- field index out of range?", field);
    }
}

void ItemDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        case FIELD_counter: pp->setCounter(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_isDiscarded: pp->setIsDiscarded(value.boolValue()); break;
        case FIELD_generationTime: pp->setGenerationTime(value.doubleValue()); break;
        case FIELD_startTime: pp->setStartTime(value.doubleValue()); break;
        case FIELD_discardTime: pp->setDiscardTime(value.doubleValue()); break;
        case FIELD_productionTime: pp->setProductionTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Item'", field);
    }
}

const char *ItemDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ItemDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ItemDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Item *pp = omnetpp::fromAnyPtr<Item>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Item'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp


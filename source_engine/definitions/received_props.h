#pragma once

//bunch of things deleted that aren't used, as well as a bunch of types we don't need changed to void*

//declarations, because visual studio is sometimes annoying to manage ;|
struct receivedprop_t;
struct receivedtable_t;

//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/public/dt_recv.h#L85
struct receivedprop_t
{
public:
    char* szVariablename;
    void* ptrRecVarType;
    int iFlags;
    int iStringBufferSize;
    int iInsideArray; //actually a bool
    const void* ptrExtraData;
    receivedprop_t* arrProp;
    void* arrLengthProxy;
    void* ptrProxyFn;
    void* preDataTableProxyFn;
    receivedtable_t* ptrDataTable;
    int iOffset;
    int iElementStrike;
    int iElements;
    const char* szParentArrayPropName;

};

//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/public/dt_recv.h#L170
struct receivedtable_t
{
public:
    receivedprop_t* ptrProps;
    int iProps;
    void* ptrDecoder;
    char* szNetTableName;
    bool bInitialized;
    bool bInMainList;
};
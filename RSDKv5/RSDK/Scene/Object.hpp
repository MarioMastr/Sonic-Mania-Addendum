#ifndef OBJECT_H
#define OBJECT_H

#if RETRO_USE_MOD_LOADER
#include <functional>
#endif

#define OBJECT_COUNT (0x400)

// 0x800 scene objects, 0x40 reserved ones, and 0x100 spare slots for creation
#define RESERVE_ENTITY_COUNT (0x40)
#define TEMPENTITY_COUNT     (0x100)
#define SCENEENTITY_COUNT    (0x800)
#define ENTITY_COUNT         (RESERVE_ENTITY_COUNT + SCENEENTITY_COUNT + TEMPENTITY_COUNT)
#define TEMPENTITY_START     (ENTITY_COUNT - TEMPENTITY_COUNT)

#define TYPE_COUNT        (0x100)
#define EDITABLEVAR_COUNT (0x100)
#define TYPEGROUP_COUNT   (0x104)

#define FOREACH_STACK_COUNT (0x400)

enum StaticObjectTypes {
    SVAR_UINT8,
    SVAR_UINT16,
    SVAR_UINT32,
    SVAR_INT8,
    SVAR_INT16,
    SVAR_INT32,
    SVAR_BOOL,
    SVAR_PTR,
    SVAR_VEC2,
    SVAR_TEXT,
    SVAR_ANIMATOR,
    SVAR_HITBOX,
    SVAR_UNKNOWN,
};

enum TypeGroups {
    GROUP_ALL     = 0,
    GROUP_CUSTOM1 = TYPE_COUNT,
    GROUP_CUSTOM2,
    GROUP_CUSTOM3,
    GROUP_CUSTOM4,
};

enum VariableTypes {
    VAR_UINT8,
    VAR_UINT16,
    VAR_UINT32,
    VAR_INT8,
    VAR_INT16,
    VAR_INT32,
    VAR_ENUM,
    VAR_BOOL,
    VAR_STRING,
    VAR_VECTOR2,
    VAR_FLOAT, // Not actually used in Sonic Mania so it's just an assumption, but this is the only thing that'd fit the 32 bit limit and make sense
    VAR_COLOUR,
};

enum ActiveFlags {
    ACTIVE_NEVER,   // never update
    ACTIVE_ALWAYS,  // always update (even if paused/frozen)
    ACTIVE_NORMAL,  // always update (unless paused/frozen)
    ACTIVE_PAUSED,  // update if paused
    ACTIVE_BOUNDS,  // update if in x & y bounds
    ACTIVE_XBOUNDS, // update only if in x bounds (y bounds dont matter)
    ACTIVE_YBOUNDS, // update only if in y bounds (x bounds dont matter)
    ACTIVE_RBOUNDS, // update based on radius boundaries (updateRange.x == radius)
};

enum DefaultObjects {
    TYPE_DEFAULTOBJECT = 0,
#if RETRO_REV02
    TYPE_DEVOUTPUT,
#endif
    TYPE_DEFAULTCOUNT, // max
};

struct UnknownStruct {
    int16 unknown1;
    int16 unknown2;
    int16 unknown3;
    int16 unknown4;
    int16 unknown5;
    int16 unknown6;
    int16 unknown7;
    int16 unknown8;
    int16 unknown9;
};

struct Object {
    int16 objectID;
    uint8 active;
};

struct Entity {
    Vector2 position;
    Vector2 scale;
    Vector2 velocity;
    Vector2 updateRange;
    int32 angle;
    int32 alpha;
    int32 rotation;
    int32 groundVel;
    int32 depth;
    uint16 group;
    uint16 objectID;
    bool32 inBounds;
    bool32 isPermanent;
    bool32 tileCollisions;
    bool32 interaction;
    bool32 onGround;
    uint8 active;
#if RETRO_REV02
    uint8 filter;
#endif
    uint8 direction;
    uint8 drawOrder;
    uint8 collisionLayers;
    uint8 collisionPlane;
    uint8 collisionMode;
    uint8 drawFX;
    uint8 inkEffect;
    uint8 visible;
    uint8 activeScreens;
};

struct EntityBase : Entity {
    void *data[0x100];
};

struct ObjectInfo {
    RETRO_HASH(hash);
#if RETRO_USE_MOD_LOADER // using std::function makes it easier to use stuff like lambdas
    std::function<void(void)> update;
    std::function<void(void)> lateUpdate;
    std::function<void(void)> staticUpdate;
    std::function<void(void)> draw;
    std::function<void(void *)> create;
    std::function<void(void)> stageLoad;
    std::function<void(void)> editorDraw;
    std::function<void(void)> editorLoad;
    std::function<void(void)> serialize;
#else
    void (*update)(void);
    void (*lateUpdate)(void);
    void (*staticUpdate)(void);
    void (*draw)(void);
    void (*create)(void *);
    void (*stageLoad)(void);
    void (*editorDraw)(void);
    void (*editorLoad)(void);
    void (*serialize)(void);
#endif
    Object **type;
    int32 entitySize;
    int32 objectSize;
#if RETRO_USE_MOD_LOADER
    ObjectInfo *inherited;
#endif
};

struct EditableVarInfo {
    uint32 hash[4];
    int32 offset;
    int32 active;
    uint8 type;
};

struct ForeachStackInfo {
    int32 id;
};

struct TypeGroupList {
    int32 entryCount;
    uint16 entries[ENTITY_COUNT];
};

extern int32 objectCount;
extern ObjectInfo objectList[OBJECT_COUNT];
extern int32 globalObjectCount;
extern int32 globalObjectIDs[OBJECT_COUNT];
extern int32 stageObjectIDs[OBJECT_COUNT];

extern EntityBase objectEntityList[ENTITY_COUNT];

extern EditableVarInfo *editableVarList;
extern int32 editableVarCount;

extern ForeachStackInfo foreachStackList[FOREACH_STACK_COUNT];
extern ForeachStackInfo *foreachStackPtr;

extern TypeGroupList typeGroups[TYPEGROUP_COUNT];

extern bool32 validDraw;

void RegisterObject(Object **structPtr, const char *name, uint32 entitySize, uint32 objectSize, void (*update)(void), void (*lateUpdate)(void),
                    void (*staticUpdate)(void), void (*draw)(void), void (*create)(void *), void (*stageLoad)(void), void (*editorDraw)(void),
                    void (*editorLoad)(void), void (*serialize)(void));

#if RETRO_USE_MOD_LOADER
void RegisterObject_STD(Object **structPtr, const char *name, uint32 entitySize, uint32 objectSize, std::function<void(void)> update,
                        std::function<void(void)> lateUpdate, std::function<void(void)> staticUpdate, std::function<void(void)> draw,
                        std::function<void(void *)> create, std::function<void(void)> stageLoad, std::function<void(void)> editorDraw,
                        std::function<void(void)> editorLoad, std::function<void(void)> serialize);
#endif

#if RETRO_REV02
void RegisterObjectContainer(Object **structPtr, const char *name, uint32 objectSize);
#endif

void LoadStaticObject(uint8 *obj, uint32 *hash, int32 dataPos);

#define RSDK_EDITABLE_VAR(object, type, var) RSDK.SetEditableVar(type, #var, object->objectID, offsetof(Entity##object, var))

inline void SetEditableVar(uint8 type, const char *name, uint8 object, int32 offset)
{
    if (editableVarCount < 255) {
        EditableVarInfo *var = &editableVarList[editableVarCount];
        GEN_HASH(name, var->hash);
        var->type   = type;
        var->offset = offset;
        var->active = true;
        editableVarCount++;
    }
}

void SetActiveVariable(int32 objectID, const char *name);
void AddEnumVariable(const char *name);

void InitObjects();
void ProcessObjects();
void ProcessPausedObjects();
void ProcessFrozenObjects();
void ProcessObjectDrawLists();

uint16 GetObjectByName(const char *name);
inline Entity *GetObjectByID(uint16 objectID) { return &objectEntityList[objectID < ENTITY_COUNT ? objectID : (ENTITY_COUNT - 1)]; }

inline int32 GetEntityID(EntityBase *entityPtr) { return (int32)(entityPtr - objectEntityList < ENTITY_COUNT ? entityPtr - objectEntityList : 0); }

int32 GetEntityCount(uint16 type, bool32 isActive);

void ResetEntityPtr(Entity *entity, uint16 type, void *data);
void ResetEntitySlot(uint16 slotID, uint16 type, void *data);
Entity *CreateEntity(uint16 type, void *data, int32 x, int32 y);

inline void CopyEntity(void *destEntity, void *srcEntity, bool32 clearSrcEntity)
{
    if (destEntity && srcEntity) {
        memcpy(destEntity, srcEntity, sizeof(EntityBase));
        if (clearSrcEntity)
            memset(srcEntity, 0, sizeof(EntityBase));
    }
}

bool32 GetActiveEntities(uint16 group, Entity **entity);
bool32 GetEntities(uint16 type, Entity **entity);

inline void BreakForeachLoop() { --foreachStackPtr; }

// CheckPosOnScreen but if range is NULL it'll use entity->updateRange
bool32 CheckOnScreen(Entity *entity, Vector2 *range);
// Checks if a position is on screen & within range
bool32 CheckPosOnScreen(Vector2 *position, Vector2 *range);

#endif // !OBJECT_H
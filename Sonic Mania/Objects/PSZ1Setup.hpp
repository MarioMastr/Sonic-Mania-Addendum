#ifndef OBJ_PSZ1SETUP_H
#define OBJ_PSZ1SETUP_H

#include "../SonicMania.hpp"

// Object Class
struct ObjectPSZ1Setup : Object {

};

// Entity Class
struct EntityPSZ1Setup : Entity {

};

// Object Struct
extern ObjectPSZ1Setup PSZ1Setup;

// Standard Entity Events
void PSZ1Setup_Update();
void PSZ1Setup_LateUpdate();
void PSZ1Setup_StaticUpdate();
void PSZ1Setup_Draw();
void PSZ1Setup_Create(void* data);
void PSZ1Setup_StageLoad();
void PSZ1Setup_EditorDraw();
void PSZ1Setup_EditorLoad();
void PSZ1Setup_Serialize();

// Extra Entity Functions


#endif //!OBJ_PSZ1SETUP_H
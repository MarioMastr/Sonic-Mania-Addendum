#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "Game.h"

// Helper Constants
#define PLAYER_PALETTE_INDEX_SONIC_OLD (2) // sonic's original palette indices, here for legacy reasons. Only exists in a few places in the final game.

#define PLAYER_PALETTE_INDEX_SONIC     (64)
#define PLAYER_PALETTE_INDEX_TAILS     (70)
#define PLAYER_PALETTE_INDEX_KNUX      (80)
#if MANIA_USE_PLUS
#define PLAYER_PALETTE_INDEX_MIGHTY (96)
#define PLAYER_PALETTE_INDEX_RAY    (113)
#define PLAYER_PALETTE_INDEX_AMY    (86)
#endif

#define PLAYER_PRIMARY_COLOR_COUNT (6)

// Helper Enums
typedef enum {
    ANI_IDLE,
    ANI_BORED_1,
    ANI_BORED_2,
    ANI_LOOK_UP,
    ANI_CROUCH,
    ANI_WALK,
    ANI_AIR_WALK,
    ANI_JOG,
    ANI_RUN,
    ANI_DASH,
    ANI_JUMP,
    ANI_SPRING_TWIRL,
    ANI_SPRING_DIAGONAL,
    ANI_SKID,
    ANI_SKID_TURN,
    ANI_SPINDASH,
    ANI_ABILITY_0,
    ANI_PUSH,
    ANI_HURT,
    ANI_DIE,
    ANI_DROWN,
    ANI_BALANCE_1,
    ANI_BALANCE_2,
    ANI_SPRING_CS,
    ANI_STAND_CS,
    ANI_FAN,
    ANI_VICTORY,
    ANI_OUTTA_HERE,
    ANI_HANG,
    ANI_HANG_MOVE,
    ANI_POLE_SWING_H,
    ANI_POLE_SWING_V,
    ANI_SHAFT_SWING,
    ANI_TURNTABLE,
    ANI_TWISTER,
    ANI_SPIRAL_RUN,
    ANI_STICK,
    ANI_PULLEY_HOLD,
    ANI_SHIMMY_IDLE,
    ANI_SHIMMY_MOVE,
    ANI_BREATHE,
    ANI_BUBBLE,
    ANI_RIDE,
    ANI_CLING,
    ANI_BUNGEE,
    ANI_TWIST_RUN,
#if MANIA_USE_PLUS
    ANI_FLUME,
#endif
    ANI_TRANSFORM,
    ANI_ABILITY_1,
    ANI_ABILITY_2,
    ANI_ABILITY_3,
    ANI_ABILITY_4,
    ANI_ABILITY_5,
    ANI_ABILITY_6,
    ANI_ABILITY_7,

    // Sonic Ability Anim Aliases
    ANI_DROPDASH = ANI_ABILITY_0,
    ANI_PEELOUT  = ANI_ABILITY_1,

    // Tails Ability Anim Aliases
    ANI_FLY            = ANI_ABILITY_1,
    ANI_FLY_TIRED      = ANI_ABILITY_2,
    ANI_FLY_LIFT       = ANI_ABILITY_3,
    ANI_FLY_LIFT_TIRED = ANI_ABILITY_4,
    ANI_SWIM           = ANI_ABILITY_5,
    ANI_SWIM_TIRED     = ANI_ABILITY_6,
    ANI_SWIM_LIFT      = ANI_ABILITY_7,

    // Knux Ability Anim Aliases
    ANI_LEDGE_PULL_UP = ANI_ABILITY_0,
    ANI_GLIDE         = ANI_ABILITY_1,
    ANI_GLIDE_DROP    = ANI_ABILITY_2,
    ANI_GLIDE_LAND    = ANI_ABILITY_3,
    ANI_GLIDE_SLIDE   = ANI_ABILITY_4,
    ANI_CLIMB_IDLE    = ANI_ABILITY_5,
    ANI_CLIMB_UP      = ANI_ABILITY_6,
    ANI_CLIMB_DOWN    = ANI_ABILITY_7,

#if MANIA_USE_PLUS
    // Mighty Ability Anim Aliases
    ANI_HAMMERDROP = ANI_ABILITY_0,
    ANI_UNSPIN     = ANI_ABILITY_1,

    // Ray Ability Anim Aliases
    ANI_HANG2    = ANI_ABILITY_0,
    ANI_FLY_UP   = ANI_ABILITY_1,
    ANI_FLY_DOWN = ANI_ABILITY_2,

    // Amy Ability Anim Aliases
    ANI_HAMMER_HIT    = ANI_ABILITY_1,
    ANI_SPIN_JUMP     = ANI_ABILITY_2,
    ANI_FREE_FALL     = ANI_ABILITY_3,
    ANI_HELI_HAMMER   = ANI_ABILITY_4,
    ANI_DASH_NOHAMMER = ANI_ABILITY_5,
    ANI_CDSPINDASH    = ANI_ABILITY_6,
#endif
} PlayerAnimationIDs;

// for "characterID" in editor
typedef enum {
    PLAYER_CHAR_NONE,
    PLAYER_CHAR_SONIC,
    PLAYER_CHAR_TAILS,
    PLAYER_CHAR_SONIC_TAILS,
    PLAYER_CHAR_KNUX,
    PLAYER_CHAR_AMY,
    PLAYER_CHAR_SONIC_KNUX,
    PLAYER_CHAR_TAILS_KNUX,
    PLAYER_CHAR_SONIC_TAILS_KNUX,
} PlayerCharacterIDS;

typedef enum {
    SHIELD_NONE,
    SHIELD_BLUE,
    SHIELD_BUBBLE,
    SHIELD_FIRE,
    SHIELD_LIGHTNING,
} ShieldTypes;

typedef enum {
    PLAYER_DEATH_NONE,
    PLAYER_DEATH_DIE_USESFX,
    PLAYER_DEATH_DIE_NOSFX,
    PLAYER_DEATH_DROWN,
} DeathTypes;

typedef enum {
    PLAYER_HURT_NONE,
    PLAYER_HURT_HASSHIELD,
    PLAYER_HURT_RINGLOSS,
    PLAYER_HURT_DIE,
} HurtTypes;

typedef enum {
    SUPERSTATE_NONE,
    SUPERSTATE_FADEIN,
    SUPERSTATE_SUPER,
    SUPERSTATE_FADEOUT,
    SUPERSTATE_DONE,
} SuperStates;

// Object Class
#if MANIA_USE_PLUS
struct ObjectPlayer {
    RSDK_OBJECT
    TABLE(int32 sonicPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 tailsPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 knuxPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x60000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x30000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x70000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x40000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x70000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x40000, -0x20000 });
    TABLE(int32 mightyPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 rayPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0x8000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 miraclePhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x14000, 0x600, 0x90000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x49A1A, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xE0000, 0x3C00, 0x8000, 0x1A00, 0x14000, 0x600, 0x90000, -0x40000, 0xB0000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x49A1A, -0x20000 });
    TABLE(int32 miracleKnuxPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x60000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x3800, 0x7000, 0x1800, 0x14000, 0x600, 0x80000, -0x40000, 0x90000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x40000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x30000, -0x20000,
            0xE0000, 0x3C00, 0x8000, 0x1A00, 0x14000, 0x600, 0x80000, -0x40000, 0xB0000, 0x1400, 0x2400, 0x600, 0xC000, 0x300, 0x40000, -0x20000 });
    TABLE(color superPalette_Sonic[18], { 0x000080, 0x0038C0, 0x0068F0, 0x1888F0, 0x30A0F0, 0x68D0F0, 0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860,
                                          0xF0E898, 0xF0E8D0, 0xF0D898, 0xF0E0B0, 0xF0E8C0, 0xF0F0D8, 0xF0F0F0, 0xF0F0F8 });
    TABLE(color superPalette_Tails[18], { 0x800801, 0xB01801, 0xD05001, 0xE07808, 0xE89008, 0xF0A801, 0x800801, 0xB01801, 0xD05001, 0xE07808,
                                          0xE89008, 0xF0A801, 0xF03830, 0xF06848, 0xF09860, 0xF0B868, 0xF0C870, 0xF0D870 });
    TABLE(color superPalette_Knux[18], { 0x580818, 0x980130, 0xD00840, 0xE82858, 0xF06080, 0xF08088, 0xF33F90, 0xF26496, 0xF787A5, 0xF99FAF, 0xFBB7BF,
                                         0xFDCECE, 0xF33F90, 0xF26496, 0xF787A5, 0xF99FAF, 0xFBB7BF, 0xFDCECE });
    TABLE(color superPalette_Mighty[18], { 0x681818, 0x942424, 0xBB2525, 0xDF3434, 0xF2604A, 0xFB916A, 0xB81919, 0xE43A3A, 0xF75F5F, 0xFC8C7E,
                                           0xFBB8A2, 0xFED0B4, 0xB81919, 0xE43A3A, 0xF75F5F, 0xFC8C7E, 0xFBB8A2, 0xFED0B4 });
    TABLE(color superPalette_Ray[18], { 0xA06800, 0xB88810, 0xD0A810, 0xE0C020, 0xE8D038, 0xF0E078, 0xE0A801, 0xF0C820, 0xF0E820, 0xF0F040, 0xF0F068,
                                        0xF0F0B8, 0xE0A801, 0xF0C820, 0xF0E820, 0xF0F040, 0xF0F068, 0xF0F0B8 });
    TABLE(color superPalette_Amy[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0xEC4F41, 0xF36F62, 0xF6887E, 0xF79F97, 0xFAB1AD,
                                        0xFDCDC9, 0xF67F74, 0xF8948B, 0xFAAFA8, 0xFCC4BF, 0xFEDEDC, 0xFEEEEB });
    TABLE(color miraclePalette_Sonic[18], { 0x000080, 0x0038C0, 0x0068F0, 0x1888F0, 0x30A0F0, 0x68D0F0, 0xBC34A3, 0xD94AB1, 0xF16AC2, 0xFF88CA,
                                            0xFEB6DE, 0xFFE0F1, 0xEE5DC1, 0xF278C7, 0xF990CF, 0xFFB2D8, 0xFFD6ED, 0xFFF0F8 });
    TABLE(color miraclePalette_Tails[18], { 0x800801, 0xB01801, 0xD05001, 0xE07808, 0xE89008, 0xF0A801, 0x7534BC, 0x9A4AD9, 0xC16AF1, 0xDC90F9,
                                            0xEDAAFD, 0xF6C3FE, 0xAF5DEE, 0xC67DF7, 0xE0A3FA, 0xEFBDFF, 0xF7D1FF, 0xFDEBFF });
    TABLE(color miraclePalette_Knux[18], { 0x580818, 0x980130, 0xD00840, 0xE82858, 0xF06080, 0xF08088, 0x39C04F, 0x28D752, 0x5DE986, 0x8CF2B2,
                                           0xB9F9D5, 0xD3FDE8, 0x4BEC64, 0x6FF190, 0x90F9B0, 0xB2FFD0, 0xD6FFE9, 0xF0FFF8 });
    TABLE(color miraclePalette_Mighty[18], { 0x681818, 0x942424, 0xBB2525, 0xDF3434, 0xF2604A, 0xFB916A, 0xBC6634, 0xD9884A, 0xF1AB6A, 0xFFCA8A,
                                             0xFEE2B4, 0xFFF6E0, 0xED9E54, 0xF2B378, 0xF9C890, 0xFFE1B2, 0xFFEFD6, 0xFFFBF0 });
    TABLE(color miraclePalette_Ray[18], { 0xA06800, 0xB88810, 0xD0A810, 0xE0C020, 0xE8D038, 0xF0E078, 0xBC3448, 0xD94A56, 0xF16A6C, 0xFF8E8A,
                                          0xFEB2AA, 0xFFE6E0, 0xEE5D73, 0xF27883, 0xF99091, 0xFFB5B2, 0xFFD1CC, 0xFFEDEB });
    TABLE(color miraclePalette_Amy[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0x519EDB, 0x5DB9E9, 0x75CEF0, 0x8EE0F5,
                                          0xA8F1FA, 0xCAFCFC, 0x5DB3EE, 0x78CCF2, 0x90DCF9, 0xB2EFFF, 0xD6FBFF, 0xF5FFFF });
    TABLE(color superPalette_Sonic_HCZ[18], { 0x200888, 0x3020C8, 0x3840F0, 0x4070F0, 0x4098F0, 0x40C0F0, 0x88C880, 0x68E090, 0x50F098, 0x68F0C0,
                                              0x78F0C8, 0xA0F0D8, 0x60E898, 0x48F0A0, 0x58F0B0, 0x68F0C0, 0x90F0D0, 0xA0F0D8 });
    TABLE(color superPalette_Tails_HCZ[18], { 0x880808, 0xA03810, 0xA05848, 0xB07058, 0xC08068, 0xC89078, 0xCC6161, 0xDC8462, 0xD5978A, 0xDEA893,
                                              0xE6B09D, 0xEABAA7, 0xCC6161, 0xDC8462, 0xD5978A, 0xDEA893, 0xE6B09D, 0xEABAA7 });
    TABLE(color superPalette_Knux_HCZ[18], { 0x181050, 0x301090, 0x5018A8, 0x8828C0, 0xA048C0, 0xB868C8, 0x746DA3, 0x7F65D0, 0x9768E0, 0xC070EF,
                                             0xD086EB, 0xDE9CED, 0x746DA3, 0x7F65D0, 0x9768E0, 0xC070EF, 0xD086EB, 0xDE9CED });
    TABLE(color superPalette_Mighty_HCZ[18], { 0x2E0D05, 0x570F0F, 0x830907, 0xA4150F, 0xBF3924, 0xCC6C45, 0x7C8F91, 0x8E9D9E, 0x95ABAD, 0x97BDBA,
                                               0x97CFC8, 0x98D9CF, 0x7C8F91, 0x8E9D9E, 0x95ABAD, 0x97BDBA, 0x97CFC8, 0x98D9CF });
    TABLE(color superPalette_Ray_HCZ[18], { 0x406090, 0x488890, 0x68A880, 0x70C080, 0x68D080, 0x50E888, 0x80B088, 0x78D090, 0x68F080, 0x50F098,
                                            0x90F0C0, 0xA8F0E0, 0x80B088, 0x78D090, 0x68F080, 0x50F098, 0x90F0C0, 0xA8F0E0 });
    TABLE(color superPalette_Amy_HCZ[18], { 0x3D1395, 0x6519B9, 0x8B38C1, 0xA958C9, 0xB278DC, 0xB598EA, 0xBA9C96, 0xBEACA6, 0xBEB9B5, 0xC0C4C1,
                                            0xC1CDCC, 0xC3DBDA, 0xBFB4AF, 0xC0BEBB, 0xC1CCC9, 0xC2D6D5, 0xC3E3E3, 0xC3EBEB });
    TABLE(color miraclePalette_Sonic_HCZ[18], { 0x200888, 0x3020C8, 0x3840F0, 0x4070F0, 0x4098F0, 0x40C0F0, 0xA28EC7, 0xB199CE, 0xBDA9D6, 0xC4B8DA,
                                                0xC3CFE4, 0xC4ECF1, 0xBBA3D6, 0xBDB0D9, 0xC1BCDD, 0xC4CDE1, 0xC4DFEB, 0xC4ECF1 });
    TABLE(color miraclePalette_Amy_HCZ[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0x61D4A7, 0x59E0B4, 0x73E9C4, 0x8AEDD3,
                                              0x9CF0DE, 0xAEF2E6, 0x6DCAE3, 0x73D7EA, 0x7FE1ED, 0x8BE9EF, 0x98EFF2, 0xA9F2F3 });
    TABLE(color superPalette_Sonic_CPZ[18], { 0x4000D8, 0x5800E0, 0x6810E0, 0x8020E0, 0xA020E0, 0xC040E0, 0xE04880, 0xE06890, 0xE078A8, 0xE078D8,
                                              0xE080E0, 0xE080E0, 0xE080B0, 0xE080B0, 0xE080C0, 0xE080C0, 0xE080E0, 0xE080E0 });
    TABLE(color superPalette_Tails_CPZ[18], { 0xC80180, 0xD00178, 0xE00180, 0xE81088, 0xE83098, 0xE84898, 0xF078F0, 0xF078F0, 0xF080F0, 0xF088F0,
                                              0xF098F0, 0xF0A0F0, 0xF078F0, 0xF078F0, 0xF080F0, 0xF088F0, 0xF098F0, 0xF0A0F0 });
    TABLE(color superPalette_Knux_CPZ[18], { 0xA00180, 0xB00178, 0xC00190, 0xD001B0, 0xE001E0, 0xE820E8, 0xF078D8, 0xF078E8, 0xF088F0, 0xF098F0,
                                             0xF0A8F0, 0xF0B0F0, 0xF078D8, 0xF078E8, 0xF088F0, 0xF098F0, 0xF0A8F0, 0xF0B0F0 });
    TABLE(color superPalette_Mighty_CPZ[18], { 0xAE3F91, 0xC04396, 0xD04497, 0xDE4A9D, 0xE65BA5, 0xE96FB2, 0xCE3F92, 0xE04C9F, 0xE85BAE, 0xEA6DBA,
                                               0xE97FC9, 0xEA88D0, 0xCE3F92, 0xE04C9F, 0xE85BAE, 0xEA6DBA, 0xE97FC9, 0xEA88D0 });
    TABLE(color superPalette_Ray_CPZ[18], { 0xE00180, 0xE00190, 0xE02898, 0xE048A8, 0xE060B8, 0xE078E0, 0xE02880, 0xE05888, 0xE08088, 0xE080A8,
                                            0xE080D8, 0xE080E0, 0xE02880, 0xE05888, 0xE08088, 0xE080A8, 0xE080D8, 0xE080E0 });
    TABLE(color superPalette_Amy_CPZ[18], { 0xA00180, 0xD80188, 0xE001A0, 0xE001B0, 0xE000D5, 0xEF00EF, 0xF16F9E, 0xF47FAF, 0xF68CBD, 0xF697C9,
                                            0xF7A0D4, 0xF9AEE2, 0xF687B8, 0xF691C3, 0xF79FD2, 0xF8A9DD, 0xF9B6EC, 0xF9BEF3 });
    TABLE(color miraclePalette_Sonic_CPZ[18], { 0x4000D8, 0x5800E0, 0x6810E0, 0x8020E0, 0xA020E0, 0xC040E0, 0xD962CF, 0xE76DD6, 0xF37DDF, 0xFA8CE3,
                                                0xF9A2ED, 0xFAB7F6, 0xF276DE, 0xF484E1, 0xF790E5, 0xFAA0EA, 0xFAB2F4, 0xFABFFA });
    TABLE(color miraclePalette_Amy_CPZ[18], { 0x64036E, 0x980F8C, 0xC02AAA, 0xEA51B5, 0xF678D0, 0xFABBE3, 0x97A7AF, 0x8FB3BD, 0xA9BCCC, 0xC1C0DB,
                                              0xD2C3E7, 0xE4C6EF, 0xA39DEB, 0xA9AAF2, 0xB5B4F6, 0xC2BCF8, 0xCFC2FB, 0xE0C5FC });
    bool32 cantSwap;
    int32 playerCount;
    uint16 upState;
    uint16 downState;
    uint16 leftState;
    uint16 rightState;
    uint16 jumpPressState;
    uint16 jumpHoldState;
    int32 nextLeaderPosID;
    int32 lastLeaderPosID;
    Vector2 leaderPositionBuffer[16];
    Vector2 targetLeaderPosition;
    int32 autoJumpTimer;
    int32 respawnTimer;
    int32 aiInputSwapTimer;
    bool32 disableP2KeyCheck;
    int32 rings;
    STATIC(int32 ringExtraLife, 100);
    int32 powerups;
    STATIC(int32 savedLives, 3);
    int32 savedScore;
    STATIC(int32 savedScore1UP, 50000);
    uint16 sonicFrames;
    uint16 superFrames;
    uint16 miracleFrames;
    uint16 tailsFrames;
    uint16 superTailsFrames;
    uint16 tailsTailsFrames;
    uint16 superTailsTailsFrames;
    uint16 miracleTailsFrames;
    uint16 miracleTailsTailsFrames;
    uint16 knuxFrames;
    uint16 superKnuxFrames;
    uint16 miracleKnuxFrames;
    uint16 mightyFrames;
    uint16 superMightyFrames;
    uint16 miracleMightyFrames;
    uint16 rayFrames;
    uint16 superRayFrames;
    uint16 miracleRayFrames;
    uint16 amyFrames;
    uint16 superAmyFrames;
    uint16 miracleAmyFrames;
    uint16 sfxJump;
    uint16 sfxRoll;
    uint16 sfxCharge;
    uint16 sfxRelease;
    uint16 sfxPeelCharge;
    uint16 sfxPeelRelease;
    uint16 sfxDropdash;
    uint16 sfxLoseRings;
    uint16 sfxHurt;
    uint16 sfxPimPom;
    uint16 sfxSkidding;
    uint16 sfxGrab;
    uint16 sfxFlying;
    bool32 playingFlySfx;
    uint16 sfxTired;
    bool32 playingTiredSfx;
    uint16 sfxLand;
    uint16 sfxSlide;
    uint16 sfxOuttahere;
    uint16 sfxTransform2;
    uint16 sfxSwap;
    uint16 sfxSwapFail;
    uint16 sfxMightyDeflect;
    uint16 sfxMightyDrill;
    uint16 sfxMightyLand;
    uint16 sfxMightyUnspin;
    int32 raySwoopTimer;
    int32 rayDiveTimer;
    bool32 gotHit[PLAYER_COUNT];
    StateMachine(configureGhostCB);
    bool32 (*canSuperCB)(bool32 isHUD);
    int32 superDashCooldown;
    uint16 sfxAmyHammer;
    uint16 sfxAmyHammerFly;
    uint16 sfx1up;
    bool32 hasReflectAchievement;
    TABLE(int32 miracleColors[32],
        { 0x4A2644, 0x2C0656, 0xFCA6DA, 0xFEC8EB, 0xFEE1F5, 0x623259, 0x8A407D, 0xC67595, 0xE5A9B4, 0xFDD6D7, 0xFFF0F0, 0x490198, 0x8A01D0, 0xC53AE9, 0xEC9FEF, 0x58CA9F,
          0x76DBB6, 0x91EDCE, 0xBEF4E2, 0x8D4311, 0xC15A15, 0xE27F22, 0xEAA939, 0xEED253, 0xEBE67A, 0x6A21B5, 0x8735ED, 0x9066F4, 0x9E93F0, 0xF990C6, 0xFDBAE4, 0x942981 });
    int32 colorStorage[32];
    TABLE(int32 miracleColors_HCZ[32],
        { 0x4A2644, 0x5B77A0, 0xC2C7E2, 0xC3D8EB, 0xC3E5EF, 0x768DA2, 0x8A94B4, 0xA7AFC0, 0xB7C9CF, 0xC3DFE1, 0xC4ECED, 0x6975C1, 0x8A75DD, 0xA791EA, 0xB8BBEB, 0x71D9C5,
          0x80E2D0, 0x8DEADC, 0xA3EEE6, 0x8B967E, 0xA5A180, 0xB5B486, 0xB9C992, 0xBBDD9F, 0xBAE7B2, 0x7A85D0, 0x888FEB, 0x8DA8EF, 0x93BEED, 0xF990C6, 0xFDBAE4, 0x942981 });
    int32 colorStorage_HCZ[32];
    TABLE(int32 miracleColors_CPZ[32],
        { 0x4A2644, 0x914BA9, 0xF89AEB, 0xF9ABF3, 0xF9B8F8, 0xAC61AA, 0xC068BC, 0xDE82C8, 0xED9CD8, 0xF9B2E9, 0xFABFF6, 0x9F48CA, 0xC048E6, 0xDD65F2, 0xEF8FF4, 0xA7ACCD,
          0xB6B5D9, 0xC3BEE5, 0xDAC1EF, 0xC16986, 0xDB7588, 0xEC878F, 0xF09C9A, 0xF2B0A7, 0xF0BABB, 0xB058D8, 0xBE62F4, 0xC37BF8, 0xCA91F6, 0xF990C6, 0xFDBAE4, 0x942981 });
    int32 colorStorage_CPZ[32];
};
#else
struct ObjectPlayer {
    RSDK_OBJECT
    int32 playerCount;
    TABLE(int32 sonicPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x80000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000 });
    TABLE(int32 tailsPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x68000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x38000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x80000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x68000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x80000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x38000, -0x20000 });
    TABLE(int32 knuxPhysicsTable[64],
          { 0x60000, 0xC00,  0x1800, 0x600,  0x8000,  0x600, 0x60000, -0x40000, 0x30000, 0x600,  0xC00,  0x300, 0x4000, 0x300, 0x30000, -0x20000,
            0xA0000, 0x3000, 0x6000, 0x1800, 0x10000, 0x600, 0x60000, -0x40000, 0x50000, 0x1800, 0x3000, 0xC00, 0x8000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x4000, 0x300, 0x30000, -0x20000,
            0xC0000, 0x1800, 0x3000, 0xC00,  0x8000,  0x600, 0x60000, -0x40000, 0x60000, 0xC00,  0x1800, 0x600, 0x8000, 0x300, 0x30000, -0x20000 });
    uint16 upState;
    uint16 downState;
    uint16 leftState;
    uint16 rightState;
    uint16 jumpPressState;
    uint16 jumpHoldState;
    int32 nextLeaderPosID;
    int32 lastLeaderPosID;
    Vector2 leaderPositionBuffer[16];
    Vector2 targetLeaderPosition;
    int32 autoJumpTimer;
    int32 respawnTimer;
    int32 aiInputSwapTimer;
#if GAME_VERSION != VER_100 // may not work with building static var files, but who's building 1.00 static var files anyways lol
    bool32 disableP2KeyCheck;
#endif
    int32 rings;
    STATIC(int32 ringExtraLife, 100);
    int32 powerups;
    STATIC(int32 savedLives, 3);
    int32 savedScore;
    STATIC(int32 savedScore1UP, 50000);
    uint16 sonicFrames;
    uint16 superFrames;
    uint16 tailsTailsFrames;
    uint16 tailsFrames;
    uint16 knuxFrames;
    TABLE(color superPalette_Sonic[18], { 0x000080, 0x0038C0, 0x0068F0, 0x1888F0, 0x30A0F0, 0x68D0F0, 0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860,
                                          0xF0E898, 0xF0E8D0, 0xF0D898, 0xF0E0B0, 0xF0E8C0, 0xF0F0D8, 0xF0F0F0, 0xF0F0F8 });
    TABLE(color superPalette_Tails[18], { 0x800801, 0xB01801, 0xD05001, 0xE07808, 0xE89008, 0xF0A801, 0xF03830, 0xF06848, 0xF09860, 0xF0B868,
                                          0xF0C870, 0xF0D870, 0xF03830, 0xF06848, 0xF09860, 0xF0B868, 0xF0C870, 0xF0D870 });
    TABLE(color superPalette_Knux[18], { 0x580818, 0x980130, 0xD00840, 0xE82858, 0xF06080, 0xF08088, 0xF05878, 0xF06090, 0xF080A0, 0xF098B0, 0xF0B0C8,
                                         0xF0C0C8, 0xF05878, 0xF06090, 0xF080A0, 0xF098B0, 0xF0B0C8, 0xF0C0C8 });
    TABLE(color superPalette_Sonic_HCZ[18], { 0x200888, 0x3020C8, 0x3840F0, 0x4070F0, 0x4098F0, 0x40C0F0, 0x88C880, 0x68E090, 0x50F098, 0x68F0C0,
                                              0x78F0C8, 0xA0F0D8, 0x60E898, 0x48F0A0, 0x58F0B0, 0x68F0C0, 0x90F0D0, 0xA0F0D8 });
    TABLE(color superPalette_Tails_HCZ[18], { 0x880808, 0xA03810, 0xA05848, 0xB07058, 0xC08068, 0xC89078, 0xCC6161, 0xDC8462, 0xD5978A, 0xDEA893,
                                              0xE6B09D, 0xEABAA7, 0xCC6161, 0xDC8462, 0xD5978A, 0xDEA893, 0xE6B09D, 0xEABAA7 });
    TABLE(color superPalette_Knux_HCZ[18], { 0x181050, 0x301090, 0x5018A8, 0x8828C0, 0xA048C0, 0xB868C8, 0x746DA3, 0x7F65D0, 0x9768E0, 0xC070EF,
                                             0xD086EB, 0xDE9CED, 0x746DA3, 0x7F65D0, 0x9768E0, 0xC070EF, 0xD086EB, 0xDE9CED });
    TABLE(color superPalette_Sonic_CPZ[18], { 0x4000D8, 0x5800E0, 0x6810E0, 0x8020E0, 0xA020E0, 0xC040E0, 0xE04880, 0xE06890, 0xE078A8, 0xE078D8,
                                              0xE080E0, 0xE080E0, 0xE080B0, 0xE080B0, 0xE080C0, 0xE080C0, 0xE080E0, 0xE080E0 });
    TABLE(color superPalette_Tails_CPZ[18], { 0xC80180, 0xD00178, 0xE00180, 0xE81088, 0xE83098, 0xE84898, 0xF078F0, 0xF078F0, 0xF080F0, 0xF088F0,
                                              0xF098F0, 0xF0A0F0, 0xF078F0, 0xF078F0, 0xF080F0, 0xF088F0, 0xF098F0, 0xF0A0F0 });
    TABLE(color superPalette_Knux_CPZ[18], { 0xA00180, 0xB00178, 0xC00190, 0xD001B0, 0xE001E0, 0xE820E8, 0xF078D8, 0xF078E8, 0xF088F0, 0xF098F0,
                                             0xF0A8F0, 0xF0B0F0, 0xF078D8, 0xF078E8, 0xF088F0, 0xF098F0, 0xF0A8F0, 0xF0B0F0 });
    uint16 sfxJump;
    uint16 sfxRoll;
    uint16 sfxCharge;
    uint16 sfxRelease;
    uint16 sfxPeelCharge;
    uint16 sfxPeelRelease;
    uint16 sfxDropdash;
    uint16 sfxLoseRings;
    uint16 sfxHurt;
    uint16 unused; // this matches up perfectly with the position of "sfxPimPom" in plus, and it cant be padding so :eye:
    uint16 sfxSkidding;
    uint16 sfxGrab;
    uint16 sfxFlying;
    bool32 playingFlySfx;
    uint16 sfxTired;
    bool32 playingTiredSfx;
    uint16 sfxLand;
    uint16 sfxSlide;
    uint16 sfxOuttahere;
    uint16 sfxTransform2;
    bool32 gotHit[PLAYER_COUNT];
};
#endif

// Entity Class
struct EntityPlayer {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(nextAirState);
    StateMachine(nextGroundState);
    EntityCamera *camera;
    Animator animator;
    Animator tailAnimator;
    int32 minJogVelocity;
    int32 minRunVelocity;
    int32 minDashVelocity;
    int32 unused; // the only used variable in the player struct, I cant find a ref to it anywhere so...
    int32 tailRotation;
    int32 tailDirection;
    uint16 aniFrames;
    uint16 tailFrames;
    uint16 animationReserve; // what anim to return to after SpringTwirl/SpringDiagonal has finished and the player is falling downwards
    uint16 playerID;
    Hitbox *outerbox;
    Hitbox *innerbox;
    int32 characterID;
    int32 rings;
    int32 ringExtraLife;
    int32 shield;
    int32 lives;
    int32 score;
    int32 score1UP;
    bool32 hyperRing;
    int32 timer;
    int32 outtaHereTimer;
    int32 abilityTimer;
    int32 spindashCharge;
    int32 abilityValue;
    int32 drownTimer;
    int32 invincibleTimer;
    int32 superInvulnTimer;
    int32 speedShoesTimer;
    int32 blinkTimer;
    int32 scrollDelay;
    int32 skidding;
    int32 pushing;
    int32 underwater;     // 0 = not in water, 1 = in palette water, else water entityID
    bool32 groundedStore; // prev frame's onGround value
    bool32 invertGravity;
    bool32 isChibi;
#if GAME_VERSION != VER_100
    bool32 isTransforming;
#endif
    int32 superState;
    bool32 miracleState;
    int32 superRingLossTimer;
    int32 superBlendAmount;
    int32 superBlendState;
    bool32 sidekick;
    int32 scoreBonus;
    int32 jumpOffset;
    int32 collisionFlagH;
    int32 collisionFlagV;
    int32 topSpeed;
    int32 acceleration;
    int32 deceleration;
    int32 airAcceleration;
    int32 airDeceleration;
    int32 skidSpeed;
    int32 rollingFriction;
    int32 rollingDeceleration;
    int32 gravityStrength;
    int32 abilitySpeed;
    int32 jumpStrength;
    int32 jumpCap;
    int32 flailing;
    int32 sensorX[5];
    int32 sensorY;
    Vector2 moveLayerPosition;
#if MANIA_USE_PLUS
    StateMachine(stateInputReplay);
#endif
    StateMachine(stateInput);
    int32 controllerID;
    int32 controlLock;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    bool32 applyJumpCap;
    int32 jumpAbilityState;
    StateMachine(stateAbility);
    StateMachine(statePeelout);
    StateMachine(stateTallJump);
    int32 flyCarryTimer;
    Vector2 flyCarrySidekickPos;
    Vector2 flyCarryLeaderPos;
    uint8 deathType;
    bool32 forceRespawn;
#if MANIA_USE_PLUS
    bool32 isGhost;
#endif
    int32 abilityValues[8];
    void *abilityPtrs[8];
#if MANIA_USE_PLUS
    int32 uncurlTimer;
    bool32 hammeractivate;
#endif
};

// Object Struct
extern ObjectPlayer *Player;

// Standard Entity Events
void Player_Update(void);
void Player_LateUpdate(void);
void Player_StaticUpdate(void);
void Player_Draw(void);
void Player_Create(void *data);
void Player_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void Player_EditorDraw(void);
void Player_EditorLoad(void);
#endif
void Player_Serialize(void);

// Extra Entity Functions
void Player_LoadSprites(void);
void Player_LoadSpritesVS(void);
void Player_SaveValues(void);
void Player_GiveScore(EntityPlayer *player, int32 score);
void Player_GiveRings(EntityPlayer *player, int32 amount, bool32 playSfx);
void Player_GiveLife(EntityPlayer *entity);
void Player_ApplyShield(EntityPlayer *player);
void Player_ChangeCharacter(EntityPlayer *entity, int32 character);
bool32 Player_TryTransform(EntityPlayer *player, uint8 emeraldMasks, uint8 timeStoneMasks);
bool32 Player_TryTransform_ERZ(EntityPlayer *player, uint8 emeraldMasks, uint8 timeStoneMasks);
void Player_BlendSuperSonicColors(int32 bankID);
void Player_BlendSuperTailsColors(int32 bankID);
void Player_BlendSuperKnuxColors(int32 bankID);
#if MANIA_USE_PLUS
void Player_BlendSuperMightyColors(int32 bankID);
void Player_BlendSuperRayColors(int32 bankID);
void Player_BlendSuperAmyColors(int32 bankID);
#endif
void Player_HandleSuperForm(void);
bool32 Player_CheckP2KeyPress(void);
// returns the pointer to the nearest player to the current entity on the x axis only
EntityPlayer *Player_GetNearestPlayerX(void);
// returns the pointer to the nearest player to the current entity on both the x & y axis
EntityPlayer *Player_GetNearestPlayer(void);
#if MANIA_USE_PLUS
void Player_RemoveEncoreLeader(void);
#endif
void Player_ResetBoundaries(EntityPlayer *player);
void Player_HandleDeath(EntityPlayer *player);
void Player_HandleQuickRespawn(EntityPlayer *player);

// Collision
// returns a pointer to the currently active player hitbox (outer box)
Hitbox *Player_GetHitbox(EntityPlayer *player);
// returns a pointer to the alternate player hitbox (inner box)
Hitbox *Player_GetAltHitbox(EntityPlayer *player);
// performs a non-solid box collision with the player, this handles setting the appropriate collision-related player variabes automatically
bool32 Player_CheckCollisionTouch(EntityPlayer *player, void *entity, Hitbox *entityHitbox);
// performs an all-solid box collision with the player, this handles setting the appropriate collision-related player variabes automatically
bool32 Player_CheckCollisionBox(EntityPlayer *player, void *entity, Hitbox *entityHitbox);
// performs a top-solid box collision with the player, this handles setting the appropriate collision-related player variabes automatically
bool32 Player_CheckCollisionPlatform(EntityPlayer *player, void *entity, Hitbox *entityHitbox);

// Hits the player if not invulnerable, returns true if player was hit
bool32 Player_Hurt(EntityPlayer *player, void *entity);
// the same as above, though the knockback dir is gotten from the player dir rather the direction of the distance
bool32 Player_HurtFlip(EntityPlayer *player);
// Hits the player if not invulnerable and the player's shield doesn't match shield, returns true if player was hit
bool32 Player_ElementHurt(EntityPlayer *player, void *entity, int32 shield);
// returns true if the player is in an "attacking" state
bool32 Player_CheckAttacking(EntityPlayer *player, void *e);
// returns true if the player is in an "attacking" state (but omits invincibility timer as being an "attacking" state)
bool32 Player_CheckAttackingNoInvTimer(EntityPlayer *player, void *e);
// checks if the player collided with an entity, this collision differs from the touch one above since it uses hammerdrop & instashield if appropriate
bool32 Player_CheckBadnikTouch(EntityPlayer *player, void *entity, Hitbox *entityHitbox);
// checks if the player is attacking the badnik, returns true if the player attacked the badnik, otherwise the player is hit and returns false
bool32 Player_CheckBadnikBreak(EntityPlayer *player, void *entity, bool32 destroy);
// similar to checkBadnikTouch, this time for bosses, handles rebounds and stuff properly, does NOT check for hammerdrop/instashield hitboxes. returns
// true if player hit the boss, otherwise the player is hit and returns false
bool32 Player_CheckBossHit(EntityPlayer *player, void *entity);
// similar to checkHit, but for projectiles, handles the rebound effect when using shields or crouching as mighty, returns true if deflected,
// otherwise the player is hit and returns false
bool32 Player_ProjectileHurt(EntityPlayer *player, void *projectile);
#if MANIA_USE_PLUS
// similar to checkHit, but for objects that should bounce off mighty's shell, returns true if deflected, otherwise the player is hit and returns
// false
bool32 Player_CheckMightyShellHit(EntityPlayer *player, void *e, int32 velX, int32 velY);
#endif
// Similar to "Player_CheckBadnikBreak" but omits the score/explosion & animal stuff. Does not destroy 'entity'
bool32 Player_CheckItemBreak(EntityPlayer *player, void *entity, bool32 hitIfNotAttacking);

// State helpers
void Player_UpdatePhysicsState(EntityPlayer *entity);
void Player_HandleIdleAnimation(void);
void Player_HandleGroundAnimation(void);
void Player_HandleGroundMovement(void);
void Player_HandleGroundRotation(void);
void Player_HandleAirRotation(void);
void Player_HandleAirMovement(void);
void Player_HandleAirFriction(void);
void Player_Action_Jump(EntityPlayer *entity);
void Player_Action_Roll(void);
void Player_Action_Spindash(void);
void Player_Action_Spindash_CD(void);
void Player_Action_Peelout(void);
void Player_Action_TallJump(void);
#if MANIA_USE_PLUS
bool32 Player_SwapMainPlayer(bool32 forceSwap);
#endif
void Player_HandleRollDeceleration(void);
void Player_Hit(EntityPlayer *player);
bool32 Player_CheckValidState(EntityPlayer *player);
void Player_HandleFlyCarry(EntityPlayer *leader);
void Player_HandleSidekickRespawn(void);
void Player_State_StartSuper(void);

// States
void Player_State_Static(void);
void Player_State_Ground(void);
void Player_State_Air(void);
void Player_State_Roll(void);
void Player_State_TubeRoll(void);
void Player_State_TubeAirRoll(void);
void Player_State_LookUp(void);
void Player_State_Crouch(void);
void Player_State_Spindash(void);
void Player_State_Spindash_CD(void);
void Player_State_Peelout(void);
void Player_State_TallJump(void);
void Player_State_OuttaHere(void);
void Player_State_Transform(void);
void Player_State_Hurt(void);
void Player_State_Death(void);
void Player_State_Drown(void);
void Player_State_DropDash(void);
void Player_State_BubbleBounce(void);
void Player_State_TailsFlight(void);
void Player_State_FlyCarried(void);
void Player_State_FlightCancel(void);
void Player_State_KnuxGlideLeft(void);
void Player_State_KnuxGlideRight(void);
void Player_State_KnuxGlideDrop(void);
void Player_State_KnuxGlideSlide(void);
void Player_State_KnuxWallClimb(void);
void Player_State_KnuxLedgePullUp(void);
#if MANIA_USE_PLUS
void Player_State_MightyHammerDrop(void);
void Player_State_MightyUnspin(void);
void Player_SpawnMightyHammerdropDust(int32 speed, Hitbox *hitbox);
bool32 Player_CheckMightyUnspin(EntityPlayer *player, int32 bounceDistance, bool32 checkHammerDrop, int32 *uncurlTimer);
void Player_State_RayGlide(void);
void Player_State_AmyHeliHammer_Left(void);
void Player_State_AmyHeliHammer_Right(void);
#endif
void Player_State_FlyToPlayer(void);
void Player_State_ReturnToPlayer(void);
void Player_State_HoldRespawn(void);
void Player_FinishedReturnToPlayer(EntityPlayer *player, EntityPlayer *leader);
void Player_State_EncoreRespawn(void);
void Player_State_Victory(void);
void Player_State_Bubble(void);
void Player_State_WaterSlide(void);
void Player_State_TransportTube(void);

// Gravity States
void Player_Gravity_True(void);
void Player_Gravity_False(void);

// Jump Ability States
void Player_JumpAbility_Sonic(void);
void Player_JumpAbility_Tails(void);
void Player_JumpAbility_Knux(void);
#if MANIA_USE_PLUS
void Player_JumpAbility_Mighty(void);
void Player_JumpAbility_Ray(void);
void Player_JumpAbility_Amy(void);
void Player_State_AmyDoubleJump(void);

bool32 Player_SfxCheck_RayDive(void);
bool32 Player_SfxCheck_RaySwoop(void);
void Player_SfxUpdate_RayDive(int32 sfxID);
void Player_SfxUpdate_RaySwoop(int32 sfxID);
#endif

// Input States
void Player_Input_P1(void);
void Player_Input_P2_Delay(void);
void Player_Input_P2_AI(void);
void Player_Input_AI_SpindashPt1(void);
void Player_Input_AI_SpindashPt2(void);
void Player_Input_P2_Player(void);

void Player_State_DrawMiracle(void);

#endif //! OBJ_PLAYER_H

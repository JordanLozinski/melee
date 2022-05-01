#include <global.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

static f32 lbl_804DDA40 = 0x43300000;
extern void func_80390228(struct _HSD_GObj*);
extern u32 Timer_UpdateSubSeconds (); // func_8016AF0C
extern u32 HSD_JObjGetFlags(HSD_JObj*);
extern void HSD_JObjSetFlagsAll(HSD_JObj* jobj, u32 unk); 
extern void HSD_JObjClearFlagsAll(struct _HSD_JObj*, unsigned int);

extern u32 MatchInfo_LoadSeconds(void); // func_8016AEEC
extern void func_8000C0E8(void*, u8, u32); // func_8000C0E8(void* hsd_obj, foo->x30, ?)
extern void func_8000C160(struct _HSD_GObj**, unsigned int);
extern void func_80390228(struct _HSD_GObj*);
extern u32 HSD_JObjGetFlags(HSD_JObj*);

extern u32 Timer_UpdateSubSeconds (); // func_8016AF0C

// TODO decomp this and remove it from iftime.s
extern void func_802F3AE8(HSD_JObj* param_1,int param_2,int param_3);

struct TimerInfo {
    void* objptr[3]; // Casted to GObj or JObj, in different contexts
    long padding[9];
    u8 timer_idx; // Speculative name. It stores 5 - the number of seconds left during the countdown. 
    u32 unused;
    HSD_JObj* mystery_jobj;
};
struct TimerInfo lbl_804A1078;

// Match_HideTimer
void func_802F405C(void) {
    long padding[6];
    struct TimerInfo * temp = &lbl_804A1078;
    if (temp->objptr[0] != NULL)
    {
        HSD_JObjSetFlagsAll(((HSD_GObj*)temp->objptr[0])->hsd_obj, 0x10);
    }
    if (temp->objptr[1] != NULL){
        
        HSD_JObjSetFlagsAll(((HSD_GObj*)temp->objptr[1])->hsd_obj, 0x10);
    }
}

void func_802F40B8(void) {
    long padding[6];
    struct TimerInfo* tinfo = &lbl_804A1078;
    HSD_JObj* uVar3;
    u32 uVar1;
    u16 uVar2;

    if (tinfo->objptr[0] != NULL) {
        uVar3 = ((HSD_GObj*)tinfo->objptr[0])->hsd_obj;
        HSD_JObjClearFlagsAll(uVar3, 0x10);
        uVar1 = func_8016AEEC();
        uVar2 = func_8016AF0C();
        func_802F3AE8(uVar3, uVar1, uVar2);
    }
    if (lbl_804A1078.objptr[1] != NULL) {
        HSD_JObjClearFlagsAll(((HSD_GObj*)lbl_804A1078.objptr[1])->hsd_obj, 0x10);
    }
}

int func_802F4144(void) {
    u16 sVar2;
    s32 iVar1;

    sVar2 = Timer_UpdateSubSeconds(); // func_8016AF0C
    iVar1 = MatchInfo_LoadSeconds();
    if ((s32)sVar2 == 0){
        iVar1 = 5 - iVar1;
    } else {
        iVar1 = 4 - iVar1;
    }

    if (iVar1 < 0) {
        iVar1 = 0;
    }
    return iVar1;
}

void func_802F480C(void) {
    struct _HSD_GObj** foo;
    foo = lbl_804A1078.objptr;
    func_8000C160(foo, 0x3c);
}

void func_802F483C(void) {
    struct _HSD_GObj** foo;
    foo = lbl_804A1078.objptr;
    if (foo[0] != NULL){
        func_80390228(foo[0]);
        foo[0] = 0;
    }
    if (foo[1] != NULL){
        func_80390228(foo[1]);
        foo[1] = 0;
    }

}

u32 func_802F4898(void) {
    struct _HSD_GObj** foo;
    long padding[6];
    foo = lbl_804A1078.objptr;
    if (foo[0] != NULL)
    {
        if (HSD_JObjGetFlags(foo[0]->hsd_obj) & 0x10)
        {
            return 1;
        }
    }
    if (foo[1] != NULL)
    {
        if (HSD_JObjGetFlags(foo[1]->hsd_obj) & 0x10)
        {
            return 1;
        }
    }
    return 0;
}

#include "../inc/uchat.h"

static void fifth_set(t_main *m) {
    char tmp20[5] ={0xF0, 0x9F, 0x98, 0xB7, '\0'};
    char tmp21[5] ={0xF0, 0x9F, 0xA4, 0xA9, '\0'};
    char tmp22[5] ={0xF0, 0x9F, 0xA4, 0xAE, '\0'};
    char tmp23[5] ={0xF0, 0x9F,0x91, 0xBB, '\0'};
    char tmp24[5] ={0xF0, 0x9F, 0x92, 0xA9, '\0'};

    m->emo->utf[20] = mx_strdup(tmp20);
    m->emo->utf[21] = mx_strdup(tmp21); 
    m->emo->utf[22] = mx_strdup(tmp22);
    m->emo->utf[23] = mx_strdup(tmp23);
    m->emo->utf[24] = mx_strdup(tmp24); 
}

static void fourth_set(t_main *m) {
    char tmp15[5] ={0xF0, 0x9F, 0xA4, 0xAC, '\0'};
    char tmp16[5] ={0xF0, 0x9F, 0x98, 0xB3, '\0'};
    char tmp17[5] ={0xF0, 0x9F, 0x98, 0x88, '\0'};
    char tmp18[5] ={0xF0, 0x9F, 0xA4, 0x94, '\0'};
    char tmp19[5] ={0xF0, 0x9F, 0x98, 0x8E, '\0'};

    m->emo->utf[15] = mx_strdup(tmp15); 
    m->emo->utf[16] = mx_strdup(tmp16); 
    m->emo->utf[17] = mx_strdup(tmp17); 
    m->emo->utf[18] = mx_strdup(tmp18); 
    m->emo->utf[19] = mx_strdup(tmp19); 
}

static void third_set(t_main *m) {
    char tmp10[5] ={0xF0, 0x9F, 0xA5, 0xB5, '\0'};
    char tmp11[5] ={0xF0, 0x9F, 0x98, 0xAD, '\0'};
    char tmp12[5] ={0xF0, 0x9F, 0xA4, 0x91, '\0'};
    char tmp13[5] ={0xF0, 0x9F, 0x98, 0x90, '\0'};
    char tmp14[5] ={0xF0, 0x9F, 0x98, 0xB1, '\0'};

    m->emo->utf[10] = mx_strdup(tmp10); 
    m->emo->utf[11] = mx_strdup(tmp11); 
    m->emo->utf[12] = mx_strdup(tmp12); 
    m->emo->utf[13] = mx_strdup(tmp13); 
    m->emo->utf[14] = mx_strdup(tmp14);
}

static void second_set(t_main *m) {
    char tmp5[5] ={0xF0, 0x9F, 0x98, 0x98, '\0'};
    char tmp6[5] ={0xF0, 0x9F, 0x98, 0xA2, '\0'};
    char tmp7[5] ={0xF0, 0x9F, 0xA4, 0xAF, '\0'};
    char tmp8[5] ={0xF0, 0x9F, 0x99, 0x84, '\0'};
    char tmp9[5] ={0xF0, 0x9F, 0x98, 0x8D, '\0'};

    m->emo->utf[5] = mx_strdup(tmp5);
    m->emo->utf[6] = mx_strdup(tmp6);
    m->emo->utf[7] = mx_strdup(tmp7);
    m->emo->utf[8] = mx_strdup(tmp8); 
    m->emo->utf[9] = mx_strdup(tmp9); 
}

void first_emo_set(t_main *m) {
    char tmp[5] ={0xF0, 0x9F, 0x98, 0xBA, '\0'};
    char tmp1[5] ={0xF0, 0x9F, 0x98, 0x84, '\0'};
    char tmp2[5] ={0xF0, 0x9F, 0x99, 0x83, '\0'};
    char tmp3[5] ={0xF0, 0x9F, 0x98, 0x86, '\0'};
    char tmp4[5] ={0xF0, 0x9F, 0x98, 0xB5, '\0'};

    m->emo->utf[0] = mx_strdup(tmp);
    m->emo->utf[1] = mx_strdup(tmp1);
    m->emo->utf[2] = mx_strdup(tmp2);
    m->emo->utf[3] = mx_strdup(tmp3);
    m->emo->utf[4] = mx_strdup(tmp4);
    second_set(m);
    third_set(m);
    fourth_set(m);
    fifth_set(m);
}

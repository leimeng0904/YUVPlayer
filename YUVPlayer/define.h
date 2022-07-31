#ifndef _DEFINE_H_
#define _DEFINE_H_


typedef     char                int8;
typedef     int                 int32;
typedef     short               int16;
typedef     unsigned char       uint8;
typedef     unsigned int        uint32;
typedef     unsigned short      uint16;
typedef     unsigned __int64    uint64;

//#define       LOGINFO

#define     TRUE                1
#define     FALSE               0

#define     ABS(X)              (((X) > 0 ) ? (X) : (-X))
#define     BIN(X, binVal)      (((X) == 0) ? 0 : binVal)

//======= ������֧�ִ򿪵����ͼ����� =======
#define     MAX_IMAGE_NUM           10

//======= ͼ��ߴ�������󳤶� =======
#define     MAX_NAME_LEN            20

//======= ��������ֵ =======
#define     FAILED_YUVPlayer        -1
#define     EOF_YUVPlayer           -2
#define     SKIP_YUVPlayer          -3
#define     SUCCEEDED_YUVPlayer     1

//======= ��������ģʽ =======
#define     COMP_MODE           0   //++ ����ͼ��Ƚ�ģʽ
#define     VIEW_MODE           1   //++ ���ͼ�����ģʽ

//======= ��תģʽ =======
#define     ROTATE_0            0   //++ ����ת
#define     ROTATE_90           1   //++ ˳ʱ����ת90��
#define     ROTATE_180          2   //++ ��ת180��
#define     ROTATE_270          3   //++ ��ʱ����ת90��

//======= ����ģʽ =======
#define     MIRROR_NONE         0   //++ �޾���
#define     MIRROR_HORI         1   //++ ˮƽ����
#define     MIRROR_VERT         2   //++ ��ֱ����
#define     MIRROR_BOTH         3   //++ ��Ͼ���

//======= ��ֵ���㷽ʽ =======
#define     BIN_MODE            0   //++ ����ֵ��ʽ����
#define     ABS_MODE            1   //++ ������ֵ��ʽ����

//======= ͼ����ʾģʽ =======
#define     IMAGE_YUV           0
#define     IMAGE_Y             1
#define     IMAGE_U             2
#define     IMAGE_V             3
#define     IMAGE_INVALID       4

//======= ͼ�������ʽ =======
#define     YUV400              0
#define     YUV420              1
#define     YUV422              2
#define     YUV444              3

//======= ����״̬ =======
#define     STOP_STATUS         0
#define     PAUSE_STATUS        1
#define     PLAY_STATUS         2

//======= ����ֵ��ʾ��ʽ =======
#define     OCT_MODE            0
#define     HEX_MODE            1

//======= �Զ�����Ϣ =======
#define     WM_MYMESSAGE_0      (WM_USER + 100) //++ ֪ͨ���̲߳����Ѿ�ֹͣ
#define     WM_MYMESSAGE_1      (WM_USER + 101) //++ ������ʾͼ��
#define     WM_MYMESSAGE_2      (WM_USER + 102) //++ ������ʾ��ֵͼ��
#define     WM_MYMESSAGE_3      (WM_USER + 103) //++ ͼ�񴰿��������ڴ��ݼ�����Ϣ
#define     WM_MYMESSAGE_4      (WM_USER + 104) //++ ֪ͨ���������´򿪵�ǰͼ��������ǰͼ��

//======= ���̰��� =======
#define     VK_A                0X41    //++ ���� A ��ĸ��
#define     VK_C                0X43    //++ ���� C ��ĸ��
#define     VK_Z                0X5A    //++ ���� Z ��ĸ��
#define     VK_R                0X52    //++ ���� R ��ĸ��
#define     VK_S                0X53    //++ ���� S ��ĸ��
#define     VK_0                0X30
#define     VK_9                0X39

//======= ����ֹͣ�������� =======
#define     PAUSE_VALUE_0       0
#define     PAUSE_VALUE_1       1
#define     PAUSE_VALUE_2       2
#define     PAUSE_VALUE_3       3
#define     PAUSE_VALUE_4       4
#define     PAUSE_VALUE_5       5
#define     PAUSE_VALUE_6       6
#define     PAUSE_VALUE_7       7
#define     PAUSE_VALUE_8       8
#define     PAUSE_VALUE_9       9
#define     PAUSE_VALUE_10      10
#define     PAUSE_VALUE_11      11
#define     PAUSE_VALUE_12      12
#define     PAUSE_VALUE_13      13
#define     PAUSE_VALUE_14      14
#define     VALUE_INVALID       -1

#endif
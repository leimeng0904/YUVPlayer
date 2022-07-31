#include "stdafx.h"
#include "colorconvert.h"
//*/
// Converter of YV12 to RGB24
// the size of pYUV is (3 * iWidth * iHeight / 2)
// and size of pRGB is (3 * iWidth * iHeight)
// if sucess return true, else return false
bool YV12toRGB24(unsigned char *yData, unsigned char *uData, unsigned char *vData, unsigned char *pRGB24, int iWidth,
                 int iHeight)
{
    unsigned int    u32RGBBufferStride   = ((iWidth * 3 + 3) >> 2) << 2;


    if (!yData || !pRGB24) {
        return false;
    }

    if (!uData || !vData) {
        return false;
    }

    const long nYLen = long(iHeight * iWidth);
    const int nHfWidth = (iWidth >> 1);

    if (nYLen < 1 || nHfWidth < 1) {
        return false;
    }

    // yv12's data structure
    // |WIDTH |
    // y......y--------
    // y......y  HEIGHT
    // y......y
    // y......y--------
    // u..u
    // u..u
    // v..v
    // v..v
    // Convert YV12 to RGB24
    //
    int rgb[3];
    int i, j, m, n, x, y;
    m = -iWidth;
    n = -nHfWidth;
    for (y = 0; y < iHeight; y++) {
        m += iWidth;
        if (!(y % 2)) {
            n += nHfWidth;
        }
        for (x = 0; x < iWidth; x++) {
            i = m + x;
            j = n + (x >> 1);
            rgb[2] = int(1.164 * (yData[i] - 16) + 1.596 * (vData[j] - 128)); // r
            rgb[1] = int(1.164 * (yData[i] - 16) - 0.813 * (vData[j] - 128) - 0.391 * (uData[j] - 128)); // g
            rgb[0] = int(1.164 * (yData[i] - 16) + 2.018 * (uData[j] - 128)); // b
//          rgb[2] = int(1.164 * (yData[i] - 16) + 1.793 * (vData[j] - 128)); // r
//          rgb[1] = int(1.164 * (yData[i] - 16) - 0.534 * (vData[j] - 128) - 0.213 * (uData[j] - 128)); // g
//          rgb[0] = int(1.164 * (yData[i] - 16) + 2.115 * (uData[j] - 128)); // b

            i = (iHeight - 1 - y) * u32RGBBufferStride + x * 3;
            for (j = 0; j < 3; j++) {
                if (rgb[j] >= 0 && rgb[j] <= 255) {
                    pRGB24[i + j] = rgb[j];
                } else {
                    pRGB24[i + j] = (rgb[j] < 0) ? 0 : 255;
                }
            }
        }
    }
    return true;
}

/*************************************************************************
 *
 * �������ƣ�
 *   Interpolation()
 *
 * ����:
 *   LPBYTE lpDest      - ָ��Ŀ��ͼ��ָ��
 *   LPBYTE lpSrc       - ָ��ԴDIBͼ��ָ��
 *   int  Wid           - Դͼ���ȣ���������
 *   int  Height        - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   void      - ����ֵ��
 *
 * ˵��:
 *   �ú�������˫���Բ�ֵ�㷨����������ֵ��
 *
 ************************************************************************/

void Interpolation(unsigned char *lpDest, unsigned char *lpSrc, int SrcWid, int SrcHeight)
{
    int i, j;
    // ���Ȱ�Դ(i,j)ֱ�����ΪĿ����(2*i+1,2*j+1)
    for (i = 0; i < SrcHeight; i++) {
        for (j = 0; j < SrcWid; j++) {
            lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 1)] = lpSrc[i * SrcWid + j];
        }
    }
    // ���Ŷ�ˮƽ��������˲�[][]to[][]
    for (i = 0; i < SrcHeight; i++) {
        for (j = 0; j < SrcWid; j++) {
            //��߽�
            //��Ҫ�������ֵʱ
            //if(2*j == 0){
            if (j == 0) {
                lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j)] = (-1 * lpDest[(2 * i + 1) * 2 * SrcWid +
                        (2 * j + 1)] + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 1)]
                        + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 1)] - lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 3)]) >> 4;
            }
            //��Ҫ���һ��ֵʱ
            //else if(2*j == 2){
            else if (j == 1) {
                lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j)] = (-1 * lpDest[(2 * i + 1) * 2 * SrcWid +
                        (2 * j - 1)] + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j - 1)]
                        + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 1)] - lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 3)]) >> 4;
            }
            //�ұ߽�
            //ֻ��Ҫ���һ��ֵ
            else if (j == SrcWid - 1) {
                lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j)] = (-1 * lpDest[(2 * i + 1) * 2 * SrcWid +
                        (2 * j - 3)] + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j - 1)]
                        + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 1)] - lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 1)]) >> 4;
            } else //���ڱ߽�ʱ
                lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j)] = (-1 * lpDest[(2 * i + 1) * 2 * SrcWid +
                        (2 * j - 3)] + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j - 1)]
                        + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 1)] - lpDest[(2 * i + 1) * 2 * SrcWid + (2 * j + 3)]) >> 4;
        }
    }
    // ���ŶԴ�ֱ��������˲�[][]to[][]
    for (i = 0; i < SrcHeight; i++) {
        for (j = 0; j < 2 * SrcWid; j++) {
            //�ϱ߽�
            //��Ҫ�����������ʱ
            if (i == 0) {
                lpDest[(2 * i) * 2 * SrcWid + j] = (-1 * lpDest[(2 * i + 1) * 2 * SrcWid + j] + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + j]
                                                    + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + j] - 1 * lpDest[(2 * i + 3) * 2 * SrcWid + j]) >> 4;
            }
            //��Ҫ���һ������ʱ
            else if (i == 1) {
                lpDest[(2 * i) * 2 * SrcWid + j] = (-1 * lpDest[(2 * i - 1) * 2 * SrcWid + j] + 9 * lpDest[(2 * i - 1) * 2 * SrcWid + j]
                                                    + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + j] - 1 * lpDest[(2 * i + 3) * 2 * SrcWid + j]) >> 4;
            }
            //�±߽�ʱ
            //ֻ��Ҫ���һ������
            else if (i == SrcHeight - 1) {
                lpDest[(2 * i) * 2 * SrcWid + j] = (-1 * lpDest[(2 * i - 3) * 2 * SrcWid + j] + 9 * lpDest[(2 * i - 1) * 2 * SrcWid + j]
                                                    + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + j] - 1 * lpDest[(2 * i + 1) * 2 * SrcWid + j]) >> 4;
            } else //���ڱ߽�ʱ
                lpDest[(2 * i) * 2 * SrcWid + j] = (-1 * lpDest[(2 * i - 3) * 2 * SrcWid + j] + 9 * lpDest[(2 * i - 1) * 2 * SrcWid + j]
                                                    + 9 * lpDest[(2 * i + 1) * 2 * SrcWid + j] - 1 * lpDest[(2 * i + 3) * 2 * SrcWid + j]) >> 4;
        }
    }

}


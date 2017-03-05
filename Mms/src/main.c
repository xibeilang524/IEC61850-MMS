/*****************************************************************************************************
* FileName:                    main.c
*
* Description:                 ϵͳ������
*                              
* Author:                      YanDengxue, Fiberhome-Fuhua
*                              
* Rev History:  
*       <Author>        <Data>        <Hardware>     <Version>        <Description>
*     YanDengxue   2011-03-29 15:30       --           1.00             Create
*****************************************************************************************************/
//====================================================================================================
// ���ļ�ʹ�õ�ͷ�ļ�
//====================================================================================================
// ��ͷ�ļ�
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>
#include <bits/signum.h>
#include <time.h>
#include <assert.h>
#include <fcntl.h>

// �Զ���ͷ�ļ�
#include "UserTypesDef.h"
#include "MmsBaseData.h"
#include "ParseCidConfig.h"
#include "MmsSocketHandle.h"
#include "Debug.h"

//====================================================================================================
// ���غ�������,�˴������ĺ��������ⲿ�ӿ�
//====================================================================================================
static void MainExit(int signum);

//====================================================================================================
// ���ļ���������ⲿ�Ľӿڱ���
//====================================================================================================
Uint8 *mms_dsp_base_addr_va = (Uint8 *)0x0;

//====================================================================================================
// ���ر�������,�˴������ı��������ⲿ�ӿ�
//====================================================================================================
static MMS_IED *p_mms_ied;

//====================================================================================================
// ����ʵ��
//====================================================================================================
//----------------------------------------------------------------------------------------------------
// �ӿں���
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//   Function: main
//      Input: int32 
//     Output: void
//     Return: int32: ����ִ�����
//Description: ϵͳ�������
//    <AUTHOR>        <MODIFYTIME>            <REASON>
//   YanDengxue     2011-03-21 16:30           Create
//----------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    char const *lv_p_cid_file_name;

    lv_p_cid_file_name = argv[1];
    if ((argc < 1) || (NULL == argv[1]))
    {
        lv_p_cid_file_name = "Device.cid";
    }

mms_dsp_base_addr_va = calloc(1, 0x100000);
if (NULL == mms_dsp_base_addr_va)
{
    TRACE("mms_dsp_base_addr_va calloc failed!");
    return NORMAL_ERROR;
}

    p_mms_ied = ParseCidConfig(lv_p_cid_file_name);
    if (NULL == p_mms_ied)
    {
        TRACE("%s parse \"%s\" failed!", argv[0], lv_p_cid_file_name);
        return NORMAL_ERROR;
    }

    printf("\n%s parse \"%s\" successful and enter to server process!\n", argv[0], lv_p_cid_file_name);

    signal(SIGTERM, MainExit);

    if (NORMAL_SUCCESS != MmsSocketHandle(p_mms_ied))
    {
        TRACE("%s server process failed!", argv[0]);
        return NORMAL_ERROR;
    }

    return NORMAL_SUCCESS;
}

//----------------------------------------------------------------------------------------------------
// ���غ���
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//   Function: MainExit
//      Input: int signum
//     Output: void
//     Return: void
//Description: SIGTERM�źŴ���
//    <AUTHOR>        <MODIFYTIME>            <REASON>
//   YanDengxue     2011-03-21 16:30           Create
//----------------------------------------------------------------------------------------------------
static void MainExit(int signum)
{
    signal(SIGCHLD, SIG_DFL);

    MmsSocketExitHandle();

    exit(NORMAL_SUCCESS);
}


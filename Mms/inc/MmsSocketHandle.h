/*****************************************************************************************************
* FileName:                    MmsSocketHandle.h
*
* Description:                 Mms Socket����
*
* Author:                      YanDengxue
*
* Rev History:
*       <Author>        <Data>        <Hardware>     <Version>        <Description>
*     YanDengxue   2010-03-29 15:30       --           1.00             Create
*****************************************************************************************************/
#ifndef _Mms_Socket_Handle_H_
#define _Mms_Socket_Handle_H_

#ifdef __cplusplus
extern "C" {
#endif

//====================================================================================================
// �ⲿ��������
//====================================================================================================
int32 MmsSocketHandle(MMS_IED const *p_mms_ied);
int32 MmsSocketExitHandle(void);

#ifdef __cplusplus
}
#endif

#endif



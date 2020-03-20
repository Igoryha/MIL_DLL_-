/*============================================================================
                      Copyright ��������
..............................................................................
��� ������     : ������ � ��������� MIL-1553
��� �����      : 1553.cpp
�����          : �������� �.�.
����           : 01.11.2010
..............................................................................
�������� ������: ������ �������� ������� ������ � ��������� MIL-1553
..............................................................................
�������:
      ������ �������������� ������� ������
	Init_BC
	RT_Init
	Sending
	Receiving
	BC_Stop
	RT_Stop
	Timer_Start
	Timer_Stop
	Timer_Current
      ������ ���������� ������� ������
	WaitInt
==============================================================================
*/
#include "stdafx.h"
#include "WDMTMKv2.cpp"
#include "Interface_NSCI.h"
#include "MKIO_func.h"
#include "FC_func.h"
#define DLLEXPORT extern "C" __declspec(dllexport)
int i;

unsigned short  Buf[32];
unsigned short Buf_2[32];
//unsigned short awBuf[32];

const int fInstMode = 1;
HANDLE hBcEvent; //�������� ���������� ��� ��
HANDLE hRtEvent; //�������� ���������� ��
TTmkEventData tmkEvD; //��������� ����������� ����������

int nTmk;

TMK_DATA wBase, wMaxBase, wLen, wState, wStatus, wTimerStatus;
unsigned long dwGoodStarts = 0, dwBusyStarts = 0, dwErrStarts = 0, dwStatStarts = 0;
unsigned long dwStarts = 0L;
TMK_DATA wSubAddr;
//������������ ���� ���� ��� �������������� �����
void MKIO_35(Word32 word_in, word16* word_out_1,word16* word_out_2);

//���������� ������ ����������� �� ���� � ����
void MKIO_Unpack_BCVM_To_NSCI_Subaddres_01(DATA_NSCI_TO_VIS *edmil);
void MKIO_Unpack_BCVM_To_NSCI_Subaddres_02(DATA_NSCI_TO_VIS *edmil);
void MKIO_Unpack_BCVM_To_NSCI_Subaddres_29(DATA_NSCI_TO_VIS *edmil);


//��������� ������ ������������ �� ���� � ����
void MKIO_Pack_NSCI_To_BCVM_Subaddres_01(DATA_NSCI_TO_VIS *edmil);

//������� ���������
word16	BCVM_Subaddres_01[32];
word16	BCVM_Subaddres_02[29];
word16	BCVM_Subaddres_29[2];

//��������� ���������
word16	NSCI_Subaddres_01[10];

////������� ������
//Subaddres_29_BCVM_GROUP	m_Subaddres_29_BCVM_GROUP;
//Subaddres_01_BCVM_NSCI	m_Subaddres_01_BCVM_NSCI;
//
////�������� ������
//Subaddres_01_NSCI_BCVM	m_Subaddres_01_NSCI_BCVM;
struct Sending_Data //��������� ��� ��
{
	unsigned short
		Word_Length, //����������� ����
		RT_Number,  //����� ����������
		BC_Number, //����� �����������
		RT_SubAddress; //��������
unsigned short Word_Buf[32]; //������ �� 32 ���� ������

};

Sending_Data Send_Data; //��������� ��� ��
int WaitInt(TMK_DATA wCtrlCode);

//������������� ��
DLLEXPORT bool Init_BC(unsigned short bcnumber); 

//�������� ������ ��
DLLEXPORT  bool Sending (unsigned short subaddr, unsigned short wlenth,unsigned short rt_addr, unsigned short *Buf, unsigned short *Buf_2, int Send_Receive);

//����� ������ ��
DLLEXPORT unsigned short ExchangeMilData (DATA_NSCI_TO_VIS *exch_data_mil);

//��������� ��
DLLEXPORT void BC_Stop(void);

//��������� ��
DLLEXPORT void RT_Stop(void);

//������������� ��
DLLEXPORT bool RT_Init(unsigned short rtaddr, unsigned short rtnumber);

//������ �������
DLLEXPORT void Timer_Start(void);

//��������� �������
DLLEXPORT void Timer_Stop(void);

//��������� �������� �������� �������
DLLEXPORT unsigned long Timer_Current(void);

//������� ������ �� �� � ��
void Send_OU(unsigned short wSubAddr, unsigned short wLen, unsigned short *Buf_2);

HANDLE hThreadInput1;
DWORD	ThreadID2;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
//������� �������� ������ �� ��; subaddr - ��������, wlenth - ����������� ����, rt_addr - ����� ����������
//*Buf - ������ �� ������ ������, receive - �� ��������/��������� 1 - ���������, 0 - ��������
DLLEXPORT bool Sending (unsigned short subaddr, unsigned short wlenth,unsigned short rt_addr, unsigned short *Buf, unsigned short *Buf_2, int Send_Receive)
{

	if (wBase > wMaxBase)
      wBase = 0;
//	wBase = base;
    bcdefbase(wBase); //������������� ����


	wLen = 32; //������������� ����������� ����
    if (wLen == 0)
      wLen = 32;
  //  for (i = 0; i < wLen; ++i)
  //    awBuf[i] = (wSubAddr<<8) | i;
	
/* Try to send data to RT until it answers with Clear Status */
    bcputw(0, CW(rt_addr, RT_RECEIVE, subaddr, wlenth)); //��������� ��������� �����
    bcputblk(1, Buf, wlenth); //���������� ��������� ����� � ����
    do
    {
      bcstartx(wBase, DATA_BC_RT | CX_STOP | CX_BUS_A | CX_NOSIG); //��������� ����� ��-��
      if (WaitInt(DATA_BC_RT))
        return false;
   }

	//�������� ������ �� ��� ��� ���� �� ������ �������� �����, �� ���������� ����� ������
	while ((tmkEvD.bcx.wResultX & (SX_ERR_MASK | SX_IB_MASK)) != 0);

/* Try to receive data from RT until it answers with Clear Status */
	
    //bcputw(0, CW(RT_ADDR, RT_TRANSMIT, wSubAddr, wLen));
	bcputw(0, CW(rt_addr, RT_TRANSMIT, subaddr, wlenth));
    do
    {
		
		//ResetEvent(hBcEvent);
      bcstartx(wBase, DATA_RT_BC | CX_STOP | CX_BUS_A | CX_NOSIG);
      if (WaitInt(DATA_RT_BC))
        return false;
    }
    while ((tmkEvD.bcx.wResultX & (SX_ERR_MASK | SX_IB_MASK)) != 0);
    bcgetblk(2, Buf_2, wlenth);

	return true;
  }

//������� ������� ���������� � �������� ���������, ����������� ����������
int WaitInt(TMK_DATA wCtrlCode)
{
/* Wait for an interrupt */
  switch (WaitForSingleObject(hBcEvent, 1000))
  {
  case WAIT_OBJECT_0: //���� ���������� ���������
    ResetEvent(hBcEvent); //���������� �������
    break;
  case WAIT_TIMEOUT:
    printf("Interrupt timeout error\n");
    return 1;
  default:
    printf("Interrupt wait error\n");
    return 1;
  }

/* Get interrupt data */
/* We do not need to check tmkEvD.nInt because bcstartx with CX_NOSIG */
/* guarantees us only single interrupt of single type nInt == 3       */
  tmkgetevd(&tmkEvD); //�������� ���������, ����������� ����������
  if (tmkEvD.bcx.wResultX & SX_IB_MASK)
  {
/* We have set bit(s) in Status Word */ 
    if (((tmkEvD.bcx.wResultX & SX_ERR_MASK) == SX_NOERR) ||
        ((tmkEvD.bcx.wResultX & SX_ERR_MASK) == SX_TOD))
    {
/* We have either no errors or Data Time Out (No Data) error */
  //   wStatus = bcgetansw(wCtrlCode);
     if (wStatus & BUSY_MASK)
/* We have BUSY bit set */
        ++dwBusyStarts;
      else
/* We have unknown bit(s) set */
        ++dwStatStarts;
//      if (kbhit())
 //       return 1;
    }
    else
    {
/* We have an error */
      ++dwErrStarts;
//      if (kbhit())
    //    return 1;
    }
  }
  else if (tmkEvD.bcx.wResultX & SX_ERR_MASK)
  {
/* We have an error */
    ++dwErrStarts;
//    if (kbhit())
//      return 1;
  }
  else
  {
/* We have a completed message */
    ++dwGoodStarts;
  }

  ++dwStarts;
//  printf("%ld %04X\n", dwGoodStarts, bcgetw(0));
//  Sleep(500);
  return 0;
}

//������������� ��
DLLEXPORT bool Init_BC(unsigned short bcnumber)
{
	/* Open driver */
  if (TmkOpen()) //�������� �������� 1553
  {
    printf("TmkOpen error\n");
    return false;
  }
/* Read configuration file */
 // if (TmkInit("bc.cfg"))
 // {
 //   printf("TmkInit error\n");
  //  return false;
  //}
  tmkconfig(bcnumber); //������� ���������� � ���������� �������� ���������� � �������� �������. 
  //���� ���������� � ����� ������� �� ���������� ��� ��� ���������� � ������� ��������, 
  //�� ������������ ��� ������. ����� ���������� ���� ������� ��������������� ���������� 
  //�������� ��������� ��� ������.
/* Find first configured device */
  for (nTmk = 0; nTmk <= MAX_TMK_NUMBER; ++nTmk)
    if (!tmkselect(nTmk))
      break;
  if (nTmk > MAX_TMK_NUMBER)
  {
    printf("tmkselect error\n");
    return false;
  }
/* Try to reset in BC mode */
  if (bcreset()) //������� ���������� ������������� ���������� ���������� � ��������� ��� � ����� ��. 
  {
    printf("bcreset error\n");
    return false;
  }
/* Define event for interrupts */
  hBcEvent = CreateEvent(NULL, TRUE, FALSE, NULL); //����������� ������� ��� ����������
  if (!hBcEvent)
  {
    printf("CreateEvent error\n");
   return false;
  }
  tmkdefevent(hBcEvent, TRUE);//������� ������ ��� ���������� ���������� ������� Windows, 
  //������� ������� ����� ������������ ��� �������������� �������� � ��������� ���������� �� ����������. 

  wBase = 0;
  wMaxBase = bcgetmaxbase();
  
  return true;
}

//���������� ������ ��
DLLEXPORT void BC_Stop(void)
{
	bcreset();
/* Close all opened things */
  CloseHandle(hBcEvent);//
  tmkdone(ALL_TMKS); //���������� ������ � �����������
  TmkClose(); //������� ��������� ������� �� ���������� ������� ��������
}

//���������� ������ ��
DLLEXPORT void RT_Stop()
{
	  bcreset();
/* Close all opened things */
  CloseHandle(hRtEvent);
  tmkdone(ALL_TMKS); //���������� ������ � �����������
  TmkClose(); //������� ��������� ������� �� ���������� ������� ��������
}

//������ ������ ��
DLLEXPORT unsigned short ExchangeMilData (DATA_NSCI_TO_VIS *exch_data_mil)
{
	int send_receive = 0; // 1 - ��������; 2 - ���������
	unsigned short uSubAddr;
	unsigned short  Buf_eors[32];

/* Wait for an interrupt */
	switch (WaitForSingleObject(hRtEvent, 10))
    {
    case WAIT_OBJECT_0:
/* New message has arrived */
      ResetEvent(hRtEvent); 
      do
      {
/* Get interrupt data */
        tmkgetevd(&tmkEvD); //��������� ������ � ����������
		//unsigned long i = tmkgetevtime();
		//unsigned long i1 = tmkgetswtimer();
/* Check interrupt type */
        if (tmkEvD.nInt == 3)
        {
          ++dwGoodStarts;
          uSubAddr = (tmkEvD.rt.wStatus >> 5) &0x1F; //�������� ��������	  
          wLen = tmkEvD.rt.wStatus & 0x1F; //�������� ����������� ����
          if (wLen == 0)
            wLen = 32;
          if ((tmkEvD.rt.wStatus & RT_DIR_MASK) == RT_RECEIVE) //���� ���������� ��� �� ���������
		  {
				rtdefsubaddr(RT_RECEIVE, uSubAddr);//������� ����������� ��������� �� � ������� 
				//�� ���������� ������ � ���� � ��������� ���������.
				rtgetblk(0, &Buf_eors, wLen); //������ ��������� ���������� ����
				//rtclrflag();//������� ���������� ���� � �������� ����� �������� ��������� ���������� �� � ������ ������ �� � �������.
				send_receive = 2;
				switch (uSubAddr)
				{
				case 1:
						memcpy(&(BCVM_Subaddres_01),Buf_eors,sizeof(BCVM_Subaddres_01));
						//���������� ������ �������� �� SA1 �� ����
						MKIO_Unpack_BCVM_To_NSCI_Subaddres_01(exch_data_mil);
					break;
				case 2:
					memcpy(&(BCVM_Subaddres_02),Buf_eors,sizeof(BCVM_Subaddres_02));
					//���������� ������ �������� �� SA1 �� ����
					MKIO_Unpack_BCVM_To_NSCI_Subaddres_02(exch_data_mil);
					break;

				case 29:
						memcpy(&(BCVM_Subaddres_29),Buf_eors,sizeof(BCVM_Subaddres_29));
						//���������� ������ �������� �� SA2 �� ����
						MKIO_Unpack_BCVM_To_NSCI_Subaddres_29(exch_data_mil);
					break;
				}
		  }
		  if ((tmkEvD.rt.wStatus & RT_DIR_MASK) == RT_TRANSMIT) //���� ���������� ��� �� ��������
		  {
				send_receive = 1; 
				switch (uSubAddr)
				{
				case 1:
					//memcpy(&(pDataIn->pBins->BINS_subaddr1),pDataIn->pBins->uBufRcvInfoKPNO,sizeof(pDataIn->pBins->BINS_subaddr1));
					//���������� ������ �������� �� SA1 �� ����
						MKIO_Pack_NSCI_To_BCVM_Subaddres_01(exch_data_mil);
						Send_OU(uSubAddr,wLen,NSCI_Subaddres_01);
					break;
				}
		  }
        }
      }
/* Loop while we have not processed all interrupts */
      while (tmkEvD.nInt != 0);
      break;
    case WAIT_TIMEOUT:
/* No new messages */
      printf("Interrupt timeout error \n");
      break;
    default:
      printf("Interrupt wait error\n");
      return false;
    }
 return send_receive;
}
//������� ������ �� �� � ��
void Send_OU(unsigned short wSubAddr, unsigned short wLen, unsigned short *Buf_2)
{
		rtdefsubaddr(RT_TRANSMIT, wSubAddr);
		rtputblk(0, Buf_2, wLen); //�������� ��������� ����������� ����
	//	rtsetflag();
}
DLLEXPORT bool RT_Init (unsigned short rtaddr, unsigned short rtnumber)
{
/* Open driver */
  if (TmkOpen())
  {
    printf("TmkOpen error\n");
    return false;
  }
/* Read configuration file */
 // if (TmkInit("rt.cfg"))
  //{
  //  printf("TmkInit error\n");
  //  return false;
 // }
  tmkconfig(rtaddr);
/* Find first configured device */
  for (nTmk = 0; nTmk <= MAX_TMK_NUMBER; ++nTmk)
    if (!tmkselect(nTmk))
      break;
  if (nTmk > MAX_TMK_NUMBER)
  {
    printf("tmkselect error\n");
    return false;
  }
/* Try to reset in RT mode */
  if (rtreset())
  {
    printf("rtreset error\n");
    return false;
  }
/* Set RT address, set flag mode, enable data irqs */
  rtdefaddress(rtnumber);
  rtdefmode(RT_BRCST_MODE);
//  rtdefmode(rtgetmode()|RT_FLAG_MODE);
//  rtdefmode(rtgetmode()&~RT_FLAG_MODE);
  rtdefirqmode(rtgetirqmode()&~RT_DATA_BL);
  rtdefirqmode(rtgetirqmode()&~RT_GENER1_BL);
  rtdefirqmode(rtgetirqmode()&~RT_GENER2_BL);

/*
  for (wSubAddr = 1; wSubAddr <= 30; ++wSubAddr)
  {
// Ready to receive, not ready to transmit
    rtdefsubaddr(RT_RECEIVE, wSubAddr);
    rtclrflag();
    rtdefsubaddr(RT_TRANSMIT, wSubAddr);
    rtclrflag();
  }
*/

/* Define event for interrupts */
  hRtEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  if (!hRtEvent)
  {
    printf("CreateEvent error\n");
    return false;
  }
  tmkdefevent(hRtEvent, TRUE);
  return true;
}
DLLEXPORT void Timer_Start(void)
{
	tmkswtimer(TIMER_32BIT | TIMER_1US); //������ �������
}
DLLEXPORT unsigned long Timer_Current(void)
{
	unsigned long curren_time = tmkgetswtimer(); //��������� �������� �������� �������
	return curren_time;
}
DLLEXPORT void Timer_Stop(void)
{
	tmkswtimer(SWTIMER_OFF); //���������� �������
}
void MKIO_35(Word32 word_in, word16* word_out_1,word16* word_out_2)
{
	*word_out_1 = word_in>>16;
	*word_out_2 = word_in&(0x0000ffff);
}

//���������� ������ ���������� �� ��������� 29
void MKIO_Unpack_BCVM_To_NSCI_Subaddres_29(DATA_NSCI_TO_VIS *edmil)
{
	UINT tmp = 0;
	//����� ������� 1
	mkioDecodInt(0, 4, 8, BCVM_Subaddres_29[0], &edmil->m_Subaddres_29_BCVM_GROUP.m_BCVM_TIME_1.hour);
	mkioDecodInt(0, 9, 14, BCVM_Subaddres_29[0], &edmil->m_Subaddres_29_BCVM_GROUP.m_BCVM_TIME_1.min);
	mkioDecodBit(15, BCVM_Subaddres_29[0], &tmp);
	edmil->m_Subaddres_29_BCVM_GROUP.m_BCVM_TIME_1.smi = tmp;
	 
	//����� ������� 2
	mkioDecodInt(0, 4, 9, BCVM_Subaddres_29[1], &edmil->m_Subaddres_29_BCVM_GROUP.m_BCVM_TIME_2.sec);
	mkioDecodInt(0, 10, 19, BCVM_Subaddres_29[1], &edmil->m_Subaddres_29_BCVM_GROUP.m_BCVM_TIME_2.msec);
}

//���������� ������ ���������� �� ��������� 01
void MKIO_Unpack_BCVM_To_NSCI_Subaddres_01(DATA_NSCI_TO_VIS *edmil)
{
	UINT tmp = 0;
	//����� ����
	mkioDecodBit(4, BCVM_Subaddres_01[0], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_MODE.BCVM_NSCI_MODE_ = tmp;
	mkioDecodBit(5, BCVM_Subaddres_01[0], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_MODE.BCVM_NSCI_BRGT_MODE = tmp;
	mkioDecodBit(6, BCVM_Subaddres_01[0], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_MODE.BCVM_NSCI_ABM = tmp;
	mkioDecodBit(14, BCVM_Subaddres_01[0], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_MODE.BCVM_NSBL = tmp;
	mkioDecodInt(0, 15, 17, BCVM_Subaddres_01[0], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_MODE.BCVM_IDO);

	//���� �������� �����
	mkioDecodBit(4, BCVM_Subaddres_01[1], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_TV_A.BCVM_TV_AR = tmp;
	mkioDecodReal(0, 5, 19, 256, BCVM_Subaddres_01[1], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_TV_A.BCVM_TV_A);

	//����������� ��������������� �����
	mkioDecodReal(0, 4, 19, 8, BCVM_Subaddres_01[2], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_TV_S.BCVM_TV_S);

	//����� 1 ��������� ���������
	mkioDecodBit(4, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_H = tmp;
	mkioDecodBit(5, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_VPR = tmp;
	mkioDecodBit(6, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_VPR_M = tmp;
	mkioDecodBit(7, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_SH_AZI = tmp;
	mkioDecodBit(8, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_IZK = tmp;
	mkioDecodBit(9, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_NP = tmp;
	mkioDecodInt(0, 10, 11,BCVM_Subaddres_01[3], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_GR);
	mkioDecodBit(12, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_NNPU_M = tmp;
	mkioDecodBit(13, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_NP_ASP = tmp;
	mkioDecodBit(14, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_M = tmp;
	mkioDecodBit(15, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_UVOD = tmp;
	mkioDecodInt(0, 16, 17,BCVM_Subaddres_01[3], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_NCU);
	mkioDecodBit(18, BCVM_Subaddres_01[3], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR1.BCVM_I_NCU_M = tmp;

	//����� 2 ��������� ���������
	mkioDecodInt(0, 4, 5,BCVM_Subaddres_01[4], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_ASI);
	mkioDecodBit(6, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_ASI_M = tmp;
	mkioDecodBit(7, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_Ny = tmp;
	mkioDecodBit(8, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_Ny_M = tmp;
	mkioDecodBit(9, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_UA = tmp;
	mkioDecodBit(10, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_UA_M = tmp;
	mkioDecodBit(11, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_UUA = tmp;
	mkioDecodBit(12, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_PVUR = tmp;
	mkioDecodBit(13, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_MZUR = tmp;
	mkioDecodBit(14, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_PR = tmp;
	mkioDecodBit(15, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_PRR = tmp;
	mkioDecodBit(16, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_PR_M = tmp;
	mkioDecodBit(17, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_PRS = tmp;
	mkioDecodBit(18, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_PRT = tmp;
	mkioDecodBit(19, BCVM_Subaddres_01[4], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR2.BCVM_I_KURS = tmp;

	//����� 3 ��������� ���������
	mkioDecodInt(0, 4, 5,BCVM_Subaddres_01[4], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_VMNC);
	mkioDecodBit(6, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_SHD = tmp;
	mkioDecodBit(7, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_DU = tmp;
	mkioDecodBit(8, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_DU_PR = tmp;
	mkioDecodBit(9, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_DT = tmp;
	mkioDecodBit(10, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_DMAX = tmp;
	mkioDecodBit(11, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_ZRP = tmp;
	mkioDecodInt(0, 12, 15,BCVM_Subaddres_01[4], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_OSHD);
	mkioDecodBit(16, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_RGUVOD = tmp;
	mkioDecodBit(17, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_OPASNO = tmp;
	mkioDecodBit(18, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_ONV = tmp;
	mkioDecodBit(19, BCVM_Subaddres_01[5], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR3.BCVM_I_PRM = tmp;

	//����� 4 ��������� ���������
	mkioDecodBit(4, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_LVNSCI = tmp;
	mkioDecodInt(0, 5, 7,BCVM_Subaddres_01[6], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_IZLOES);
	mkioDecodBit(8, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_IZLOES_M = tmp;
	mkioDecodBit(9, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_RL = tmp;
	mkioDecodBit(10, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_RL_M = tmp;
	mkioDecodBit(11, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_SA = tmp;
	mkioDecodBit(12, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_SV = tmp;
	mkioDecodBit(13, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_OZC = tmp;
	mkioDecodBit(14, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_SGT = tmp;
	mkioDecodBit(15, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_SG = tmp;
	mkioDecodBit(16, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_PG = tmp;
	mkioDecodBit(17, BCVM_Subaddres_01[6], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_SPR4.BCVM_I_PG_M = tmp;

	//������ ��������������� �������������
	mkioDecodReal(1, 5, 19, 16383, BCVM_Subaddres_01[7], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_HBAR.BCVM_HBAR);

	//�������� ���������
	mkioDecodReal(0, 4, 19, 819.2, BCVM_Subaddres_01[8], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_VPR.BCVM_VPR);

	//���� �������
	mkioDecodReal(0, 4, 19, 327.675, BCVM_Subaddres_01[9], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_.BCVM_PSI);

	//���� ��������
	mkioDecodReal(0, 4, 19, 327.675, BCVM_Subaddres_01[10], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PSI_Z.BCVM_PSI_Z);

	//����� �
	mkioDecodReal(0, 4, 15, 2.048, BCVM_Subaddres_01[11], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCMV_NSCI_M.BCVM_M);

	//���������� ���������� �������������
	mkioDecodReal(0, 5, 12, 12.75, BCVM_Subaddres_01[12], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_nyf.BCVM_nyf);

	//���� �����
	mkioDecodReal(1, 5, 19, 163.835,BCVM_Subaddres_01[13], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_ALFA.BCVM_ALFA);

	//���� ������� ����������
	mkioDecodReal(1, 5, 19, 90,BCVM_Subaddres_01[14], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_TETA_TRAEK.BCVM_TETA_TRAEK);

	//���� �������
	mkioDecodReal(1, 5, 19, 1.57079632679,BCVM_Subaddres_01[15], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GAMMA.BCVM_GAMMA);

	//������ �������
	mkioDecodReal(1, 5, 19, 1.57079632679,BCVM_Subaddres_01[16], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_TETA.BCVM_TETA);

	//����� 1
	mkioDecodInt(0, 4, 7, BCVM_Subaddres_01[17], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GRZ1.BCVM_TG_VP);
	mkioDecodInt(0, 8, 10, BCVM_Subaddres_01[17], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GRZ1.BCVM_TG_VV);
	mkioDecodInt(0, 12, 19, BCVM_Subaddres_01[17], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GRZ1.BCVM_NNPU);

	//����� ������ �� �-�
	mkioDecodReal(0, 4, 12, 150,BCVM_Subaddres_01[18], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PVUR.BCVM_PVUR);

	//�������� �������� ���
	mkioDecodReal(0, 13, 19, 50,BCVM_Subaddres_01[18], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PVUR.BCVM_PRM);

	//����� �� ������� ���� �� �-�
	mkioDecodReal(0, 4, 12, 150,BCVM_Subaddres_01[19], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_MZUR.BCVM_MZUR);

	//��������� �������� ��
	mkioDecodInt(0, 4, 7, BCVM_Subaddres_01[20], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PR.BCVM_PRS);
	mkioDecodInt(0, 8, 10, BCVM_Subaddres_01[20], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PR.BCVM_PRT1);
	mkioDecodInt(0, 11, 13, BCVM_Subaddres_01[20], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PR.BCVM_PRT2);
	mkioDecodInt(0, 14, 16, BCVM_Subaddres_01[20], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PR.BCVM_PRT3);
	mkioDecodInt(0, 17, 19, BCVM_Subaddres_01[20], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_PR.BCVM_PRT4);

	//�������������� ������ �������� ����� ��/����� ��
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_01[21], 90,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_NC_FIG.BCVM_NC_FIG);

	//������������ ������ �������� ����� ��/����� ��
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_01[22], 90,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_NC_FIV.BCVM_NC_FIV);

	//��������� �� ��
	mkioDecodBit(4, BCVM_Subaddres_01[23], &tmp);
	edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_D_NC.BCVM_NC_PRD = tmp;
	mkioDecodReal(0, 5, 18, BCVM_Subaddres_01[23], 819.15, &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_D_NC.BCVM_NC_D);

	//����� ��
	mkioDecodInt(0, 4, 13, BCVM_Subaddres_01[24], &edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GT_N.BCVM_GT_N);

	//��������������� ������ ��
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_01[25], 90,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GT_FIG.BCVM_GT_FIG);

	//������������ ������ ��
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_01[26], 90,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GT_FIV.BCVM_GT_FIV);

	//��������� �� ��
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_01[27], 819.15,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_GT_D.BCVM_GT_L);

	//�max
	mkioDecodReal(0, 4, 19, BCVM_Subaddres_01[28], 512,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_D_MAX.BCVM_D_MAX);

	//�min
	mkioDecodReal(0, 4, 19, BCVM_Subaddres_01[29], 512,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_D_MIN.BCVM_D_MIN);

	//����
	mkioDecodReal(0, 4, 19, BCVM_Subaddres_01[30], 512,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_D_TEK.BCVM_D_TEK);

	//������
	mkioDecodReal(0, 4, 19, BCVM_Subaddres_01[31], 512,&edmil->m_Subaddres_01_BCVM_NSCI.m_BCVM_NSCI_D_UVOD.BCVM_D_UVOD);
}

//���������� ������ ���������� �� ��������� 02

void MKIO_Unpack_BCVM_To_NSCI_Subaddres_02(DATA_NSCI_TO_VIS *edmil)
{
	UINT tmp = 0;
	//����� ��1
	mkioDecodInt(0, 4, 11, BCVM_Subaddres_02[0], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC1_2.BCVM_VC1_N);
	//����� ��2
	mkioDecodInt(0, 12, 19, BCVM_Subaddres_02[0], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC1_2.BCVM_VC2_N);
	//����� ��3
	mkioDecodInt(0, 4, 11, BCVM_Subaddres_02[1], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC3_4.BCVM_VC3_N);
	//����� ��4
	mkioDecodInt(0, 12, 19, BCVM_Subaddres_02[1], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC3_4.BCVM_VC4_N);
	//����� ��5
	mkioDecodInt(0, 4, 11, BCVM_Subaddres_02[2], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC5_6.BCVM_VC5_N);
	//����� ��6
	mkioDecodInt(0, 12, 19, BCVM_Subaddres_02[2], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC5_6.BCVM_VC6_N);
	//����� ��7
	mkioDecodInt(0, 4, 11, BCVM_Subaddres_02[3], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC7_8.BCVM_VC7_N);
	//����� ��8
	mkioDecodInt(0, 12, 19, BCVM_Subaddres_02[3], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_VC7_8.BCVM_VC8_N);

	//�������������� ������ ����� ��1
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[4], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC1_FIG.BCVM_VC1_FIG);

	//������������ ������ ����� ��1
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[5], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC1_FIV.BCVM_VC1_FIV);
	
	//������� ������� ��������� �� ��1
	mkioDecodBit(19, BCVM_Subaddres_02[5], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC1_FIV.BCVM_VC1_PRD = tmp;

	//��������� �� ��1
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[6], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC1_D.BCVM_VC1_D);

	//��� ����� ��1
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[6], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC1_D.BCVM_VC1_T);

	//������ �� �� � � ���
	mkioDecodReal(0, 5, 12, BCVM_Subaddres_02[7], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC_Q.BCVM_VC_Q);

	//�������������� ������ ����� ��2
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[8], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC2_FIG.BCVM_VC2_FIG);

	//������������ ������ ����� ��2
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[9], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC2_FIV.BCVM_VC2_FIV);

	//������� ������� ��������� �� ��2
	mkioDecodBit(19, BCVM_Subaddres_02[9], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC2_FIV.BCVM_VC2_PRD = tmp;

	//��������� �� ��2
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[10], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC2_D.BCVM_VC2_D);

	//��� ����� ��2
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[10], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC2_D.BCVM_VC2_T);

	//�������������� ������ ����� ��3
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[11], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC3_FIG.BCVM_VC3_FIG);

	//������������ ������ ����� ��3
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[12], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC3_FIV.BCVM_VC3_FIV);

	//������� ������� ��������� �� ��3
	mkioDecodBit(19, BCVM_Subaddres_02[12], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC3_FIV.BCVM_VC3_PRD = tmp;

	//��������� �� ��3
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[13], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC3_D.BCVM_VC3_D);

	//��� ����� ��3
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[14], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC3_D.BCVM_VC3_T);

	//�������������� ������ ����� ��4
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[15], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC4_FIG.BCVM_VC4_FIG);

	//������������ ������ ����� ��4
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[16], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC4_FIV.BCVM_VC4_FIV);

	//������� ������� ��������� �� ��4
	mkioDecodBit(19, BCVM_Subaddres_02[16], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC4_FIV.BCVM_VC4_PRD = tmp;

	//��������� �� ��4
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[17], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC4_D.BCVM_VC4_D);

	//��� ����� ��4
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[17], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC4_D.BCVM_VC4_T);

	//�������������� ������ ����� ��5
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[18], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC5_FIG.BCVM_VC5_FIG);

	//������������ ������ ����� ��5
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[19], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC5_FIV.BCVM_VC5_FIV);

	//������� ������� ��������� �� ��5
	mkioDecodBit(19, BCVM_Subaddres_02[19], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC5_FIV.BCVM_VC5_PRD = tmp;

	//��������� �� ��5
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[20], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC5_D.BCVM_VC5_D);

	//��� ����� ��5
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[20], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC5_D.BCVM_VC5_T);

	//�������������� ������ ����� ��6
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[21], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC6_FIG.BCVM_VC6_FIG);

	//������������ ������ ����� ��6
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[22], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC6_FIV.BCVM_VC6_FIV);

	//������� ������� ��������� �� ��6
	mkioDecodBit(19, BCVM_Subaddres_02[22], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC6_FIV.BCVM_VC6_PRD = tmp;

	//��������� �� ��6
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[23], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC6_D.BCVM_VC6_D);

	//��� ����� ��6
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[23], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC6_D.BCVM_VC6_T);

	//�������������� ������ ����� ��7
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[24], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC7_FIG.BCVM_VC7_FIG);

	//������������ ������ ����� ��7
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[25], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC7_FIV.BCVM_VC7_FIV);

	//������� ������� ��������� �� ��7
	mkioDecodBit(19, BCVM_Subaddres_02[25], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC7_FIV.BCVM_VC7_PRD = tmp;

	//��������� �� ��7
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[26], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC7_D.BCVM_VC7_D);

	//��� ����� ��7
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[26], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC7_D.BCVM_VC7_T);

	//�������������� ������ ����� ��8
	mkioDecodReal(1, 5, 19, BCVM_Subaddres_02[27], 90,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC8_FIG.BCVM_VC8_FIG);

	//������������ ������ ����� ��8
	mkioDecodReal(1, 5, 18, BCVM_Subaddres_02[28], 45,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC8_FIV.BCVM_VC8_FIV);

	//������� ������� ��������� �� ��8
	mkioDecodBit(19, BCVM_Subaddres_02[28], &tmp);
	edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC8_FIV.BCVM_VC8_PRD = tmp;

	//��������� �� ��8
	mkioDecodReal(0, 4, 17, BCVM_Subaddres_02[29], 819.15,&edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC8_D.BCVM_VC8_D);

	//��� ����� ��8
	mkioDecodInt(0, 18, 19, BCVM_Subaddres_02[29], &edmil->m_Subaddres_02_BCVM_NSCI.m_BCVM_NSCI_VC8_D.BCVM_VC8_T);

}

//��������� ������, ������������ �� ��������� 01
void MKIO_Pack_NSCI_To_BCVM_Subaddres_01(DATA_NSCI_TO_VIS *edmil)
{
	//������� ����� ����
	mkioCodInt(0, 4, 5, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_RB, &NSCI_Subaddres_01[0]);
	mkioCodBit(6, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_RKZ, &NSCI_Subaddres_01[0]);
	mkioCodBit(7, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_RBSH, &NSCI_Subaddres_01[0]);
	mkioCodBit(8, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_BRGT_MODE, &NSCI_Subaddres_01[0]);
	mkioCodInt(0, 12, 13, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_angle_status, &NSCI_Subaddres_01[0]);
	mkioCodBit(14, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_angle_source, &NSCI_Subaddres_01[0]);
	mkioCodInt(0, 15, 16, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_offset_status, &NSCI_Subaddres_01[0]);
	mkioCodInt(0, 17, 19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SM.NSCI_IDO, &NSCI_Subaddres_01[0]);

	//������� ��������� ����
	mkioCodBit(4, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_BNSH, &NSCI_Subaddres_01[1]);
	mkioCodBit(5, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_BUSP, &NSCI_Subaddres_01[1]);
	mkioCodBit(6, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_OLU_L, &NSCI_Subaddres_01[1]);
	mkioCodBit(7, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_OLU_P, &NSCI_Subaddres_01[1]);
	mkioCodBit(8, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_NISP_P, &NSCI_Subaddres_01[1]);
	mkioCodBit(9, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_NISP_SH, &NSCI_Subaddres_01[1]);
	mkioCodBit(10, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_LS_OLU_L, &NSCI_Subaddres_01[1]);
	mkioCodBit(11, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_LS_OLU_P, &NSCI_Subaddres_01[1]);
	mkioCodBit(12, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_FCAV, &NSCI_Subaddres_01[1]);
	mkioCodBit(13, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_FCAV_BUSP, &NSCI_Subaddres_01[1]);
	mkioCodBit(14, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_PU, &NSCI_Subaddres_01[1]);
	mkioCodBit(15, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_I, &NSCI_Subaddres_01[1]);
	mkioCodBit(16, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_BCH, &NSCI_Subaddres_01[1]);
	mkioCodBit(17, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_BCVM_PA1, &NSCI_Subaddres_01[1]);
	mkioCodBit(18, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_BCVM_PA2, &NSCI_Subaddres_01[1]);
	mkioCodBit(19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_SS.NSCI_I_BCVM_PA29, &NSCI_Subaddres_01[1]);

	//�������������� ������ ��
	mkioCodReal(1, 5, 19,edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_Fi_G.NSCI_Fi_G,  163.835, &NSCI_Subaddres_01[2]);

	//������������ ������ ��
	mkioCodReal(1, 5, 19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_Fi_V.NSCI_Fi_V, 163.835, &NSCI_Subaddres_01[3]);

	//���� �������� ����� �� �����
	mkioCodReal(1, 5, 19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_GAMMA_SH.NSCI_GAMMA_SH, 163.835, &NSCI_Subaddres_01[4]);

	//�������� ����� �� ��� � ���
	mkioCodReal(1, 5, 19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_DX.NSCI_DX, 819.175, &NSCI_Subaddres_01[5]);

	//�������� ����� �� ��� Y ���
	mkioCodReal(1, 5, 19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_DY.NSCI_DY, 819.175, &NSCI_Subaddres_01[6]);

	//�������� ����� �� ��� Z ���
	mkioCodReal(1, 5, 19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_DZ.NSCI_DZ, 819.175, &NSCI_Subaddres_01[7]);

	//����� ������� 1 ������������ ��������� ��
	mkioCodInt(0, 4, 8, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_TIME_1.NSCI_HOUR, &NSCI_Subaddres_01[8]);
	mkioCodInt(0, 9, 14, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_TIME_1.NSCI_MIN, &NSCI_Subaddres_01[8]);

	//����� ������� 2 ������������ ��������� ��
	mkioCodInt(0, 4, 9, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_TIME_2.NSCI_SEC, &NSCI_Subaddres_01[9]);
	mkioCodInt(0, 10, 19, edmil->m_Subaddres_01_NSCI_BCVM.m_NSCI_BCVM_TIME_2.NSCI_MSEC, &NSCI_Subaddres_01[9]);
}
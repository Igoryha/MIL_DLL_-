#pragma once
#define Pi 3.14159265358979323846
////////////////////////////////////////////////////////////////
//Subaddres_29
//BCVM_1 -> GROUP
//Normal
//Line - MKIO_IUS
#pragma pack(push,1)
//����� ������� 1
struct BCVM_TIME_1
{
	int		hour;	//��� ������� �������
	int		min;	//������ ������� �������
	bool	smi;	//����� ���������
};

//����� ������� 2
struct BCVM_TIME_2
{
	int		sec;	//������� ������� �������
	int		msec;	//������������ ������� �������
};

////////////////////////////////////////////////////////////////
//Subaddres_01
//BCVM_1 -> NSCI
//Normal
//Line - MKIO_IUS

//����� ����
struct BCVM_NSCI_MODE
{
		bool	BCVM_NSCI_MODE_;	//����� ����
		bool    BCVM_NSCI_BRGT_MODE;//����� ���������� �������� 0-���� 1-����
		bool	BCVM_NSCI_ABM;		//�.6=1 - �������������� ������������ ������� ���������, ������������ ��� BCVM_NSCI_BRGT_MODE=0
		bool	BCVM_NSBL;			//�� ���� ������ ���
		int		BCVM_IDO;			//��������� �������� ������
};

//���� �������� �����
struct BCVM_NSCI_TV_A
{
	bool	BCVM_TV_AR;	//�������������� �������
	double		BCVM_TV_A;	//���� �������� �����
};

//����������� ��������������� �����
struct BCVM_NSCI_TV_S
{
	double	BCVM_TV_S;	//����������� ��������������� �����
};

//����� 1 ��������� ���������
struct BCVM_NSCI_SPR1
{
	bool	BCVM_I_H;		//��������� ������
	bool	BCVM_I_VPR;		//��������� ��������� �������� 
	bool	BCVM_I_VPR_M;	//��������� ��������� �������� � ������������ ������
	bool	BCVM_I_SH_AZI;	//����� ������� �� ����
	bool	BCVM_I_IZK;		//������ ��������� �����
	bool	BCVM_I_NP;		//����������� �����������
	int		BCVM_I_GR;		//������������ ���������� �����
	bool	BCVM_I_NNPU_M;	//����� ����/������� �� ���� � ������������ ������
	bool	BCVM_I_NP_ASP;	//������������� ���������� ���
	bool	BCVM_I_M;		//��������� ����� M
	bool	BCVM_I_UVOD;	//������ "����"
	int		BCVM_I_NCU;		//������� �� (��-��/��-��)
	bool	BCVM_I_NCU_M;	//������� �� (��-��/��-��) � ������������ ������
};

//����� 2 ��������� ���������
struct BCVM_NSCI_SPR2
{
	int		BCVM_I_ASI;		//������� ��� (���-��/���-��)
	bool	BCVM_I_ASI_M;	//������� ��� (���-��/���-��) � ������������ ������
	bool	BCVM_I_Ny;		//��������� ���������� ����������
	bool	BCVM_I_Ny_M;	//��������� ���������� ���������� � ������������ ������
	bool	BCVM_I_UA;		//��������� ���� �����
	bool	BCVM_I_UA_M;	//��������� ���� ����� � ������������ ������
	bool	BCVM_I_UUA;		//��������� ���� �����
	bool	BCVM_I_PVUR;	//�������������� ����� ������ �� �-� (�������� ���������, ����������� ����������� ��������)
	bool	BCVM_I_MZUR;	//����� ������� ���� �� �-�
	bool	BCVM_I_PR;		//������� "������ ���������" (��)
	bool	BCVM_I_PRR;		//������� "������ ���������" (��) ������
	bool	BCVM_I_PR_M;	//������� "������ ���������" � ������������ ������
	bool	BCVM_I_PRS;		//������� ��
	bool	BCVM_I_PRT;		//����� ��
	bool	BCVM_I_KURS;	//��������� �������� ����� ��������
};
//����� 3 ��������� ���������
struct BCVM_NSCI_SPR3
{
	int		BCVM_I_VMNC;	//�������� ����� �� 
	bool	BCVM_I_SHD;		//����� ���������
	bool	BCVM_I_DU;		//������ � �����
	bool	BCVM_I_DU_PR;	//������ � ����� � ������������ ������
	bool	BCVM_I_DT;		//������ � �������
	bool	BCVM_I_DMAX;	//������ �max
	bool	BCVM_I_ZRP;		//���� ����������� ������
	int		BCVM_I_OSHD;	//������� ����� ���������
	bool	BCVM_I_RGUVOD;	//��������� ������ "����"
	bool	BCVM_I_OPASNO;	//����������� "������"
	bool	BCVM_I_ONV;		//����������� "���" (�������)
	bool	BCVM_I_PRM;		//����������� "���" (��������������� ������)
};
//����� 4 ��������� ���������
struct BCVM_NSCI_SPR4
{
	bool	BCVM_I_LVNSCI;	//��������� ���� ������� �� ���� ��� ����������
	int		BCVM_I_IZLOES;	//��������� 101��-�/101��-�
	bool	BCVM_I_IZLOES_M;//��������� 101��-�/101��-�  � ������������ ������
	bool	BCVM_I_RL;		//��������� �-121
	bool	BCVM_I_RL_M;	//��������� �-121 � ������������ ������
	bool	BCVM_I_SA;		//������ "�"
	bool	BCVM_I_SV;		//������ "��"
	bool	BCVM_I_OZC;		//������� ������� �
	bool	BCVM_I_SGT;		//������ �� ��������
	bool	BCVM_I_SG;		//������ ����� ���������
	bool	BCVM_I_PG;		//���������� � ��������� "��"
	bool	BCVM_I_PG_M;	//���������� � ��������� "��" � ������������ ������
};

//������ ��������������� �������������
struct BCVM_NSCI_HBAR
{
	double		BCVM_HBAR;	//������ ��������������� �������������
};

//�������� ���������
struct BCVM_NSCI_VPR
{
	double		BCVM_VPR;	//�������� ���������
};


//���� �������
struct BCVM_NSCI_
{
	double		BCVM_PSI;	//���� �������
};

//���� ��������
struct BCVM_NSCI_PSI_Z
{
	double		BCVM_PSI_Z;	//���� ��������
};

//����� M
struct BCMV_NSCI_M
{
	double		BCVM_M;	//����� M
};

//���������� ���������� �������������
struct BCVM_NSCI_nyf
{
	double		BCVM_nyf;	//���������� ���������� �������������
};

//���� �����
struct BCVM_NSCI_ALFA
{
	double		BCVM_ALFA;	//���� �����
};

//���� ������� ����������
struct BCVM_NSCI_TETA_TRAEK
{
	double		BCVM_TETA_TRAEK;	//���� �����
};

//���� �������
struct BCVM_NSCI_GAMMA
{
	double		BCVM_GAMMA;	//���� �������
};
//������ �������
struct BCVM_NSCI_TETA
{
	double		BCVM_TETA;	//������ �������
};

//����� 1
struct BCVM_NSCI_GRZ1
{
	int		BCVM_TG_VP;	//��� ����� �-�
	int		BCVM_TG_VV;	//��� ����� �-�
	int		BCVM_NNPU;	//������� ����
};

//����� ������ �� �-�
struct BCVM_NSCI_PVUR
{
	double	BCVM_PVUR; //����� ������ �� �-�
	double	BCVM_PRM;  //�������� �������� ���
};

//����� �� ������� ���� �� �-�
struct BCVM_NSCI_MZUR
{
	double	BCVM_MZUR; //BCVM_MZUR
};

//�� ��� ����� ��������
struct BCVM_NSCI_PR
{
	int BCVM_PRS;	//�������� �������� ��
	int	BCVM_PRT1;	//������� �� ��� ��1
	int	BCVM_PRT2;	//������� �� ��� ��2
	int	BCVM_PRT3;	//������� �� ��� ��3
	int	BCVM_PRT4;	//������� �� ��� ��4
};

//�������������� ������ �������� ����� ����� ��
struct BCVM_NSCI_NC_FIG
{
	double		BCVM_NC_FIG;	//�������������� ������ �������� ����� ����� ��
};
//������������ ������ �������� ����� ����� ��
struct BCVM_NSCI_NC_FIV
{
	double		BCVM_NC_FIV;	//������������ ������ �������� ����� ����� ��
};

//��������� �� ��
struct BCVM_NSCI_D_NC
{
	bool		BCVM_NC_PRD;//������� ������� ��������� �� ��
	double		BCVM_NC_D;	//��������� �� ��
};

//����� ��
struct BCVM_NSCI_GT_N
{
	int			BCVM_GT_N;   //����� ��
};

//�������������� ������ ��
struct BCVM_NSCI_GT_FIG

{
	double		BCVM_GT_FIG;	//�������������� ������ ��
};

//������������ ������ ��
struct BCVM_NSCI_GT_FIV
{
	double		BCVM_GT_FIV;	//��������� �� ��
};

//��������� �� ��
struct BCVM_NSCI_GT_D
{
	double		BCVM_GT_L;	//��������� �� ��
};


//�max
struct BCVM_NSCI_D_MAX
{
	double		BCVM_D_MAX;	//�max
};
//�min
struct BCVM_NSCI_D_MIN
{
	double		BCVM_D_MIN;	//�min
};
//����
struct BCVM_NSCI_D_TEK
{
	double		BCVM_D_TEK;	//����
};
//������
struct BCVM_NSCI_D_UVOD
{
	double		BCVM_D_UVOD;	//������
};


////////////////////////////////////////////////////////////////
//Subaddres_01
//NSCI -> BCVM_1
//Normal
//Line - MKIO_IUS

//������� ����� ����
struct NSCI_BCVM_SM
{
	int		NSCI_RB;			//������� ����� ����
	bool	NSCI_RKZ;			//����������� �������� ��������
	bool	NSCI_RBSH;			//������ ��� �����
	bool	NSCI_BRGT_MODE;		//������� ����� ���������� ��������
	int		NSCI_angle_status;	//������������� ����������� �����
	bool	NSCI_angle_source;	//�������� ����������� �����
	int		NSCI_offset_status;	//������������� ����������� ��������
	int		NSCI_IDO;			//��������� �������� ������
};

//������� ��������� ����
struct NSCI_BCVM_SS
{
	bool	NSCI_I_BNSH;		//����������� ����� ����������
	bool	NSCI_I_BUSP;		//����������� ����� ���������� ������� ����������������
	bool	NSCI_I_OLU_L;		//����������� ���-�
	bool	NSCI_I_OLU_P;		//����������� ���-�
	bool	NSCI_I_NISP_P;		//����������� ����-�
	bool	NSCI_I_NISP_SH;		//����������� ����-�
	bool	NSCI_I_LS_OLU_L;	//����������� �� ���-�
	bool	NSCI_I_LS_OLU_P;	//����������� �� ���-�
	bool	NSCI_I_FCAV;		//������� ������ �� ����� FC-AV ����� ���� � ����
	bool	NSCI_I_FCAV_BUSP;	//����������� ����� FC-AV ����� ����� � ��
	bool	NSCI_I_PU;			//����������� ������ ����������
	bool	NSCI_I_I;			//������������ ����������� ����
	bool	NSCI_I_BCH;			//����������� �������� ����� ����
	bool	NSCI_I_BCVM_PA1;	//������� ������ �� ���� �� �� 1
	bool	NSCI_I_BCVM_PA2;	//������� ������ �� ���� �� �� 2
	bool	NSCI_I_BCVM_PA29;	//������� ������ �� ���� �� �� 29
};

//�������������� ������ ��
struct NSCI_BCVM_Fi_G
{
	double		NSCI_Fi_G;		//�������������� ������ �� � ���
};
//������������ ������ ��
struct NSCI_BCVM_Fi_V
{
	double		NSCI_Fi_V;		//������������ ������ �� � ���
};
//���� �������� ����� �� �����
struct NSCI_BCVM_GAMMA_SH
{
	double		NSCI_GAMMA_SH;	//���� �������� ����� �� �����
};
//�������� ����� �� ��� � ���
struct NSCI_BCVM_DX
{
	double		NSCI_DX;		//�������� ����� �� ��� � ���
};
//�������� ����� �� ��� Z ���
struct NSCI_BCVM_DY
{
	double		NSCI_DY;		//�������� ����� �� ��� Z ���
};
//�������� ����� �� ��� Y ���
struct NSCI_BCVM_DZ
{
	double		NSCI_DZ;		//�������� ����� �� ��� Y ���
};

//����� ��1,2
struct BCVM_VC1_2
{
	int			BCVM_VC1_N;		//����� ��1
	int			BCVM_VC2_N;		//����� ��2
};

//����� ��3,4
struct BCVM_VC3_4
{
	int			BCVM_VC3_N;		//����� ��3
	int			BCVM_VC4_N;		//����� ��4
};

//����� ��5,6
struct BCVM_VC5_6
{
	int			BCVM_VC5_N;		//����� ��5
	int			BCVM_VC6_N;		//����� ��6
};

//����� ��7,8
struct BCVM_VC7_8
{
	int			BCVM_VC7_N;		//����� ��7
	int			BCVM_VC8_N;		//����� ��8
};

//�������������� ������ ����� ��1
struct BCVM_NSCI_VC1_FIG
{
	double			BCVM_VC1_FIG;		//�������������� ������ ����� ��1
};

//������������ ������ ����� ��1
struct BCVM_NSCI_VC1_FIV
{
	double			BCVM_VC1_FIV;		//������������ ������ ����� ��1
	int				BCVM_VC1_PRD;		//������� ������� ��������� �� ��1
};

//��������� �� ��1
struct BCVM_NSCI_VC1_D
{
	double			BCVM_VC1_D;		//��������� �� ��1
	int				BCVM_VC1_T;		//��� ����� ��1
};

//������ �� �� � � ���
struct BCVM_NSCI_VC_Q
{
	double			BCVM_VC_Q;		//������ �� �� � � ���
};


//�������������� ������ ����� ��2
struct BCVM_NSCI_VC2_FIG
{
	double			BCVM_VC2_FIG;		//�������������� ������ ����� ��2
};

//������������ ������ ����� ��2
struct BCVM_NSCI_VC2_FIV
{
	double			BCVM_VC2_FIV;		//������������ ������ ����� ��2
	int				BCVM_VC2_PRD;		//������� ������� ��������� �� ��2
};

//��������� �� ��2
struct BCVM_NSCI_VC2_D
{
	double			BCVM_VC2_D;		//��������� �� ��2
	int				BCVM_VC2_T;		//��� ����� ��2
};

//�������������� ������ ����� ��3
struct BCVM_NSCI_VC3_FIG
{
	double			BCVM_VC3_FIG;		//�������������� ������ ����� ��3
};

//������������ ������ ����� ��3
struct BCVM_NSCI_VC3_FIV
{
	double			BCVM_VC3_FIV;		//������������ ������ ����� ��3
	int				BCVM_VC3_PRD;		//������� ������� ��������� �� ��3
};

//��������� �� ��3
struct BCVM_NSCI_VC3_D
{
	double			BCVM_VC3_D;		//��������� �� ��3
	int				BCVM_VC3_T;		//��� ����� ��3
};

//�������������� ������ ����� ��4
struct BCVM_NSCI_VC4_FIG
{
	double			BCVM_VC4_FIG;		//�������������� ������ ����� ��4
};

//������������ ������ ����� ��4
struct BCVM_NSCI_VC4_FIV
{
	double			BCVM_VC4_FIV;		//������������ ������ ����� ��4
	int				BCVM_VC4_PRD;		//������� ������� ��������� �� ��4
};

//��������� �� ��4
struct BCVM_NSCI_VC4_D
{
	double			BCVM_VC4_D;		//��������� �� ��4
	int				BCVM_VC4_T;		//��� ����� ��4
};

//�������������� ������ ����� ��5
struct BCVM_NSCI_VC5_FIG
{
	double			BCVM_VC5_FIG;		//�������������� ������ ����� ��5
};

//������������ ������ ����� ��5
struct BCVM_NSCI_VC5_FIV
{
	double			BCVM_VC5_FIV;		//������������ ������ ����� ��5
	int				BCVM_VC5_PRD;		//������� ������� ��������� �� ��5
};

//��������� �� ��5
struct BCVM_NSCI_VC5_D
{
	double			BCVM_VC5_D;		//��������� �� ��5
	int				BCVM_VC5_T;		//��� ����� ��5
};

//�������������� ������ ����� ��6
struct BCVM_NSCI_VC6_FIG
{
	double			BCVM_VC6_FIG;		//�������������� ������ ����� ��6
};

//������������ ������ ����� ��6
struct BCVM_NSCI_VC6_FIV
{
	double			BCVM_VC6_FIV;		//������������ ������ ����� ��6
	int				BCVM_VC6_PRD;		//������� ������� ��������� �� ��6
};

//��������� �� ��6
struct BCVM_NSCI_VC6_D
{
	double			BCVM_VC6_D;		//��������� �� ��6
	int				BCVM_VC6_T;		//��� ����� ��6
};

//�������������� ������ ����� ��7
struct BCVM_NSCI_VC7_FIG
{
	double			BCVM_VC7_FIG;		//�������������� ������ ����� ��7
};

//������������ ������ ����� ��7
struct BCVM_NSCI_VC7_FIV
{
	double			BCVM_VC7_FIV;		//������������ ������ ����� ��7
	int				BCVM_VC7_PRD;		//������� ������� ��������� �� ��7
};

//��������� �� ��7
struct BCVM_NSCI_VC7_D
{
	double			BCVM_VC7_D;		//��������� �� ��7
	int				BCVM_VC7_T;		//��� ����� ��7
};

//�������������� ������ ����� ��8
struct BCVM_NSCI_VC8_FIG
{
	double			BCVM_VC8_FIG;		//�������������� ������ ����� ��8
};

//������������ ������ ����� ��8
struct BCVM_NSCI_VC8_FIV
{
	double			BCVM_VC8_FIV;		//������������ ������ ����� ��8
	int				BCVM_VC8_PRD;		//������� ������� ��������� �� ��8
};

//��������� �� ��8
struct BCVM_NSCI_VC8_D
{
	double			BCVM_VC8_D;		//��������� �� ��8
	int				BCVM_VC8_T;		//��� ����� ��8
};



//����� ������� 1 ������������ ��������� ��
struct NSCI_BCVM_TIME_1
{
	int		NSCI_HOUR;		//��� ��������� ��������� ��
	int		NSCI_MIN;		//������ ��������� ��������� ��
};
//����� ������� 2 ������������ ��������� ��
struct NSCI_BCVM_TIME_2
{
	int		NSCI_SEC;		//������� ��������� ��������� ��
	int		NSCI_MSEC;		//������������ ��������� ��������� ��
};


//�������� 29. ������ ����� ���
struct Subaddres_29_BCVM_GROUP
{
	BCVM_TIME_1	m_BCVM_TIME_1;
	BCVM_TIME_2	m_BCVM_TIME_2;
};

//�������� 01. ���������� ��������� ��� ����
struct Subaddres_01_BCVM_NSCI
{
	BCVM_NSCI_MODE		m_BCVM_NSCI_MODE;
	BCVM_NSCI_TV_A		m_BCVM_NSCI_TV_A;
	BCVM_NSCI_TV_S		m_BCVM_NSCI_TV_S;
	BCVM_NSCI_SPR1		m_BCVM_NSCI_SPR1;
	BCVM_NSCI_SPR2		m_BCVM_NSCI_SPR2;
	BCVM_NSCI_SPR3		m_BCVM_NSCI_SPR3;
	BCVM_NSCI_SPR4		m_BCVM_NSCI_SPR4;
	BCVM_NSCI_HBAR		m_BCVM_NSCI_HBAR;
	BCVM_NSCI_VPR		m_BCVM_NSCI_VPR;
	BCVM_NSCI_			m_BCVM_NSCI_;
	BCVM_NSCI_PSI_Z		m_BCVM_NSCI_PSI_Z;
	BCMV_NSCI_M			m_BCMV_NSCI_M;
	BCVM_NSCI_nyf		m_BCVM_NSCI_nyf;
	BCVM_NSCI_ALFA		m_BCVM_NSCI_ALFA;
	BCVM_NSCI_TETA_TRAEK m_BCVM_NSCI_TETA_TRAEK;
	BCVM_NSCI_GAMMA		m_BCVM_NSCI_GAMMA;
	BCVM_NSCI_TETA		m_BCVM_NSCI_TETA;
	BCVM_NSCI_GRZ1		m_BCVM_NSCI_GRZ1;
	BCVM_NSCI_PVUR		m_BCVM_NSCI_PVUR;
	BCVM_NSCI_MZUR		m_BCVM_NSCI_MZUR;
	BCVM_NSCI_PR		m_BCVM_NSCI_PR;
	BCVM_NSCI_NC_FIG	m_BCVM_NSCI_NC_FIG;
	BCVM_NSCI_NC_FIV	m_BCVM_NSCI_NC_FIV;
	BCVM_NSCI_D_NC		m_BCVM_NSCI_D_NC;
	BCVM_NSCI_GT_N		m_BCVM_NSCI_GT_N;
	BCVM_NSCI_GT_FIG	m_BCVM_NSCI_GT_FIG;
	BCVM_NSCI_GT_FIV	m_BCVM_NSCI_GT_FIV;
	BCVM_NSCI_GT_D		m_BCVM_NSCI_GT_D;
	BCVM_NSCI_D_MAX		m_BCVM_NSCI_D_MAX;
	BCVM_NSCI_D_MIN		m_BCVM_NSCI_D_MIN;
	BCVM_NSCI_D_TEK		m_BCVM_NSCI_D_TEK;
	BCVM_NSCI_D_UVOD	m_BCVM_NSCI_D_UVOD;
	
};

//�������� 02. ���������� ��������� ��� ����
struct Subaddres_02_BCVM_NSCI
{
	BCVM_VC1_2			m_BCVM_VC1_2;
	BCVM_VC3_4			m_BCVM_VC3_4;
	BCVM_VC5_6			m_BCVM_VC5_6;
	BCVM_VC7_8			m_BCVM_VC7_8;
	BCVM_NSCI_VC1_FIG	m_BCVM_NSCI_VC1_FIG;
	BCVM_NSCI_VC1_FIV	m_BCVM_NSCI_VC1_FIV;
	BCVM_NSCI_VC1_D		m_BCVM_NSCI_VC1_D;
	BCVM_NSCI_VC_Q		m_BCVM_NSCI_VC_Q;
	BCVM_NSCI_VC2_FIG	m_BCVM_NSCI_VC2_FIG;
	BCVM_NSCI_VC2_FIV	m_BCVM_NSCI_VC2_FIV;
	BCVM_NSCI_VC2_D		m_BCVM_NSCI_VC2_D;
	BCVM_NSCI_VC3_FIG	m_BCVM_NSCI_VC3_FIG;
	BCVM_NSCI_VC3_FIV	m_BCVM_NSCI_VC3_FIV;
	BCVM_NSCI_VC3_D		m_BCVM_NSCI_VC3_D;
	BCVM_NSCI_VC4_FIG	m_BCVM_NSCI_VC4_FIG;
	BCVM_NSCI_VC4_FIV	m_BCVM_NSCI_VC4_FIV;
	BCVM_NSCI_VC4_D		m_BCVM_NSCI_VC4_D;
	BCVM_NSCI_VC5_FIG	m_BCVM_NSCI_VC5_FIG;
	BCVM_NSCI_VC5_FIV	m_BCVM_NSCI_VC5_FIV;
	BCVM_NSCI_VC5_D		m_BCVM_NSCI_VC5_D;
	BCVM_NSCI_VC6_FIG	m_BCVM_NSCI_VC6_FIG;
	BCVM_NSCI_VC6_FIV	m_BCVM_NSCI_VC6_FIV;
	BCVM_NSCI_VC6_D		m_BCVM_NSCI_VC6_D;
	BCVM_NSCI_VC7_FIG	m_BCVM_NSCI_VC7_FIG;
	BCVM_NSCI_VC7_FIV	m_BCVM_NSCI_VC7_FIV;
	BCVM_NSCI_VC7_D		m_BCVM_NSCI_VC7_D;
	BCVM_NSCI_VC8_FIG	m_BCVM_NSCI_VC8_FIG;
	BCVM_NSCI_VC8_FIV	m_BCVM_NSCI_VC8_FIV;
	BCVM_NSCI_VC8_D		m_BCVM_NSCI_VC8_D;


};



//�������� 01. ��������� ����
struct Subaddres_01_NSCI_BCVM
{
	NSCI_BCVM_SM		m_NSCI_BCVM_SM;
	NSCI_BCVM_SS		m_NSCI_BCVM_SS;
	NSCI_BCVM_Fi_G		m_NSCI_BCVM_Fi_G;
	NSCI_BCVM_Fi_V		m_NSCI_BCVM_Fi_V;
	NSCI_BCVM_GAMMA_SH	m_NSCI_BCVM_GAMMA_SH;
	NSCI_BCVM_DX		m_NSCI_BCVM_DX;
	NSCI_BCVM_DY		m_NSCI_BCVM_DY;
	NSCI_BCVM_DZ		m_NSCI_BCVM_DZ;
	NSCI_BCVM_TIME_1	m_NSCI_BCVM_TIME_1;
	NSCI_BCVM_TIME_2	m_NSCI_BCVM_TIME_2;
};
//��������� ������ ������� � ����������� MIL
struct DATA_NSCI_TO_VIS 
{
	//�������� ������
	Subaddres_01_NSCI_BCVM m_Subaddres_01_NSCI_BCVM;
    //������� ������
	Subaddres_01_BCVM_NSCI m_Subaddres_01_BCVM_NSCI;
	//������� ������
	Subaddres_02_BCVM_NSCI m_Subaddres_02_BCVM_NSCI;
	//�����
	Subaddres_29_BCVM_GROUP m_Subaddres_29_BCVM_GROUP;

};
#pragma pack(pop)
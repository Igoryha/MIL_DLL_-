#pragma once
#define Pi 3.14159265358979323846
////////////////////////////////////////////////////////////////
//Subaddres_29
//BCVM_1 -> GROUP
//Normal
//Line - MKIO_IUS
#pragma pack(push,1)
//Слово времени 1
struct BCVM_TIME_1
{
	int		hour;	//Час единого времени
	int		min;	//Минута единого времени
	bool	smi;	//смена источника
};

//Слово времени 2
struct BCVM_TIME_2
{
	int		sec;	//Секунда единого времени
	int		msec;	//Миллисекунда единого времени
};

////////////////////////////////////////////////////////////////
//Subaddres_01
//BCVM_1 -> NSCI
//Normal
//Line - MKIO_IUS

//Режим НСЦИ
struct BCVM_NSCI_MODE
{
		bool	BCVM_NSCI_MODE_;	//Режим НСЦИ
		bool    BCVM_NSCI_BRGT_MODE;//Режим Управления яркостью 0-день 1-ночь
		bool	BCVM_NSCI_ABM;		//р.6=1 - автоматическая регулиировка яркости запрещена, используется при BCVM_NSCI_BRGT_MODE=0
		bool	BCVM_NSBL;			//ЛВ НСЦИ внутри ИУП
		int		BCVM_IDO;			//Индикатор динамики обмена
};

//Угол поворота видео
struct BCVM_NSCI_TV_A
{
	bool	BCVM_TV_AR;	//Автоматический поворот
	double		BCVM_TV_A;	//Угол поворота видео
};

//Коэффициент масштабирования видео
struct BCVM_NSCI_TV_S
{
	double	BCVM_TV_S;	//Коэффициент масштабирования видео
};

//Слово 1 признаков индикации
struct BCVM_NSCI_SPR1
{
	bool	BCVM_I_H;		//Индикатор высоты
	bool	BCVM_I_VPR;		//Индикатор приборной скорости 
	bool	BCVM_I_VPR_M;	//Индикатор приборной скорости в проблесковом режиме
	bool	BCVM_I_SH_AZI;	//Шкала азимута ЛВ НСЦИ
	bool	BCVM_I_IZK;		//Индекс заданного курса
	bool	BCVM_I_NP;		//Неподвижное перекрестие
	int		BCVM_I_GR;		//Наименование выбранного груза
	bool	BCVM_I_NNPU_M;	//Выбор ННПУ/остаток БК ННПУ в проблесковом режиме
	bool	BCVM_I_NP_ASP;	//Невозможность применения АСП
	bool	BCVM_I_M;		//Индикатор числа M
	bool	BCVM_I_UVOD;	//Символ "УВОД"
	int		BCVM_I_NCU;		//Наличие ЦУ (ЦУ-ВЦ/ЦУ-НЦ)
	bool	BCVM_I_NCU_M;	//Наличие ЦУ (ЦУ-ВЦ/ЦУ-НЦ) в проблесковом режиме
};

//Слово 2 признаков индикации
struct BCVM_NSCI_SPR2
{
	int		BCVM_I_ASI;		//Наличие АСИ (АСИ-ВЦ/АСИ-НЦ)
	bool	BCVM_I_ASI_M;	//Наличие АСИ (АСИ-ВЦ/АСИ-НЦ) в проблесковом режиме
	bool	BCVM_I_Ny;		//Индикатор нормальной перегрузки
	bool	BCVM_I_Ny_M;	//Индикатор нормальной перегрузки в проблесковом режиме
	bool	BCVM_I_UA;		//Индикатор угла атаки
	bool	BCVM_I_UA_M;	//Индикатор угла атаки в проблесковом режиме
	bool	BCVM_I_UUA;		//Указатель угла атаки
	bool	BCVM_I_PVUR;	//Прогнозируемое время полета УР В-В (цифровой индикатор, графическое изображение счетчика)
	bool	BCVM_I_MZUR;	//Метка захвата АРГС УР В-В
	bool	BCVM_I_PR;		//Признак "Работа разрешена" (ПР)
	bool	BCVM_I_PRR;		//Признак "Работа разрешена" (ПР) ручной
	bool	BCVM_I_PR_M;	//Признак "Работа разрешена" в проблесковом режиме
	bool	BCVM_I_PRS;		//Счетчик ПР
	bool	BCVM_I_PRT;		//Табло ПР
	bool	BCVM_I_KURS;	//Индикатор текущего курса самолета
};
//Слово 3 признаков индикации
struct BCVM_NSCI_SPR3
{
	int		BCVM_I_VMNC;	//Визирная марка НЦ 
	bool	BCVM_I_SHD;		//Шкала дальности
	bool	BCVM_I_DU;		//Индекс Д увода
	bool	BCVM_I_DU_PR;	//Индекс Д увода в проблесковом режиме
	bool	BCVM_I_DT;		//Индекс Д текущей
	bool	BCVM_I_DMAX;	//Индекс Дmax
	bool	BCVM_I_ZRP;		//Зона разрешенных пусков
	int		BCVM_I_OSHD;	//Масштаб шкалы дальности
	bool	BCVM_I_RGUVOD;	//Включение режима "УВОД"
	bool	BCVM_I_OPASNO;	//Транспарант "ОПАСНО"
	bool	BCVM_I_ONV;		//Транспарант "ОТВ" (отворот)
	bool	BCVM_I_PRM;		//Транспарант "ПРМ" (противоракетный маневр)
};
//Слово 4 признаков индикации
struct BCVM_NSCI_SPR4
{
	bool	BCVM_I_LVNSCI;	//Индикатор угла наклона ЛВ НСЦИ над горизонтом
	int		BCVM_I_IZLOES;	//Излучение 101КС-В/101КС-Н
	bool	BCVM_I_IZLOES_M;//Излучение 101КС-В/101КС-Н  в проблесковом режиме
	bool	BCVM_I_RL;		//Излучение Ш-121
	bool	BCVM_I_RL_M;	//Излучение Ш-121 в проблесковом режиме
	bool	BCVM_I_SA;		//Символ "А"
	bool	BCVM_I_SV;		//Символ "СВ"
	bool	BCVM_I_OZC;		//Область захвата Ц
	bool	BCVM_I_SGT;		//Символ ГТ маршрута
	bool	BCVM_I_SG;		//Символ линии горизонта
	bool	BCVM_I_PG;		//Приведение к горизонту "ПГ"
	bool	BCVM_I_PG_M;	//Приведение к горизонту "ПГ" в проблесковом режиме
};

//Высота барометрическая относительная
struct BCVM_NSCI_HBAR
{
	double		BCVM_HBAR;	//Высота барометрическая относительная
};

//Скорость приборная
struct BCVM_NSCI_VPR
{
	double		BCVM_VPR;	//Скорость приборная
};


//Курс текущий
struct BCVM_NSCI_
{
	double		BCVM_PSI;	//Курс текущий
};

//Курс заданный
struct BCVM_NSCI_PSI_Z
{
	double		BCVM_PSI_Z;	//Курс заданный
};

//Число M
struct BCMV_NSCI_M
{
	double		BCVM_M;	//Число M
};

//Перегрузка нормальная фильтрованная
struct BCVM_NSCI_nyf
{
	double		BCVM_nyf;	//Перегрузка нормальная фильтрованная
};

//Угол атаки
struct BCVM_NSCI_ALFA
{
	double		BCVM_ALFA;	//Угол атаки
};

//Угол наклона траектории
struct BCVM_NSCI_TETA_TRAEK
{
	double		BCVM_TETA_TRAEK;	//Угол атаки
};

//Крен текущий
struct BCVM_NSCI_GAMMA
{
	double		BCVM_GAMMA;	//Крен текущий
};
//Тангаж текущий
struct BCVM_NSCI_TETA
{
	double		BCVM_TETA;	//Тангаж текущий
};

//Грузы 1
struct BCVM_NSCI_GRZ1
{
	int		BCVM_TG_VP;	//Тип груза В-П
	int		BCVM_TG_VV;	//Тип груза В-В
	int		BCVM_NNPU;	//Остаток ННПУ
};

//Время полета УР В-В
struct BCVM_NSCI_PVUR
{
	double	BCVM_PVUR; //Время полета УР В-В
	double	BCVM_PRM;  //Значение счетчика ПРМ
};

//Время до захвата АРГС УР В-В
struct BCVM_NSCI_MZUR
{
	double	BCVM_MZUR; //BCVM_MZUR
};

//ПР для точек подвески
struct BCVM_NSCI_PR
{
	int BCVM_PRS;	//Значение счетчика ПР
	int	BCVM_PRT1;	//Признак ПР для ТП1
	int	BCVM_PRT2;	//Признак ПР для ТП2
	int	BCVM_PRT3;	//Признак ПР для ТП3
	int	BCVM_PRT4;	//Признак ПР для ТП4
};

//Горизонтальный пеленг визирной метки марки НЦ
struct BCVM_NSCI_NC_FIG
{
	double		BCVM_NC_FIG;	//Горизонтальный пеленг визирной метки марки НЦ
};
//Вертикальный пеленг визирной метки марки НЦ
struct BCVM_NSCI_NC_FIV
{
	double		BCVM_NC_FIV;	//Вертикальный пеленг визирной метки марки НЦ
};

//Дальность до НЦ
struct BCVM_NSCI_D_NC
{
	bool		BCVM_NC_PRD;//Признак наличия дальности до НЦ
	double		BCVM_NC_D;	//Дальность до НЦ
};

//Номер ГТ
struct BCVM_NSCI_GT_N
{
	int			BCVM_GT_N;   //Номер ГТ
};

//Горизонтальный пеленг ГТ
struct BCVM_NSCI_GT_FIG

{
	double		BCVM_GT_FIG;	//Горизонтальный пеленг ГТ
};

//Вертикальный пеленг ГТ
struct BCVM_NSCI_GT_FIV
{
	double		BCVM_GT_FIV;	//Дальность до НЦ
};

//Дальность до ГТ
struct BCVM_NSCI_GT_D
{
	double		BCVM_GT_L;	//Дальность до ГТ
};


//Дmax
struct BCVM_NSCI_D_MAX
{
	double		BCVM_D_MAX;	//Дmax
};
//Дmin
struct BCVM_NSCI_D_MIN
{
	double		BCVM_D_MIN;	//Дmin
};
//Дтек
struct BCVM_NSCI_D_TEK
{
	double		BCVM_D_TEK;	//Дтек
};
//Дувода
struct BCVM_NSCI_D_UVOD
{
	double		BCVM_D_UVOD;	//Дувода
};


////////////////////////////////////////////////////////////////
//Subaddres_01
//NSCI -> BCVM_1
//Normal
//Line - MKIO_IUS

//Текущий режим НСЦИ
struct NSCI_BCVM_SM
{
	int		NSCI_RB;			//Текущий режим НСЦИ
	bool	NSCI_RKZ;			//Расширенный контроль завершен
	bool	NSCI_RBSH;			//Работа без шлема
	bool	NSCI_BRGT_MODE;		//Текущий режим управления яркостью
	int		NSCI_angle_status;	//Достоверность вычисленных углов
	bool	NSCI_angle_source;	//Источник вычисленных углов
	int		NSCI_offset_status;	//Достоверность вычисленных смещений
	int		NSCI_IDO;			//Индикатор динамики обмена
};

//Текущее состояние НСЦИ
struct NSCI_BCVM_SS
{
	bool	NSCI_I_BNSH;		//Исправность блока нашлемного
	bool	NSCI_I_BUSP;		//Исправность блока управления системы позиционирования
	bool	NSCI_I_OLU_L;		//Исправность ОЛУ-Л
	bool	NSCI_I_OLU_P;		//Исправность ОЛУ-П
	bool	NSCI_I_NISP_P;		//Исправность НИСП-П
	bool	NSCI_I_NISP_SH;		//Исправность НИСП-Ш
	bool	NSCI_I_LS_OLU_L;	//Исправность ЛС ОЛУ-Л
	bool	NSCI_I_LS_OLU_P;	//Исправность ЛС ОЛУ-П
	bool	NSCI_I_FCAV;		//Наличие обмена по линии FC-AV между БПТС и НСЦИ
	bool	NSCI_I_FCAV_BUSP;	//Исправность линии FC-AV между БУСПИ и НБ
	bool	NSCI_I_PU;			//Исправность пульта управления
	bool	NSCI_I_I;			//Интегральная исправность НСЦИ
	bool	NSCI_I_BCH;			//Исправность бортовой части НСЦИ
	bool	NSCI_I_BCVM_PA1;	//Наличие обмена от БЦВМ по ПА 1
	bool	NSCI_I_BCVM_PA2;	//Наличие обмена от БЦВМ по ПА 2
	bool	NSCI_I_BCVM_PA29;	//Наличие обмена от БЦВМ по ПА 29
};

//Горизонтальный пеленг ЛВ
struct NSCI_BCVM_Fi_G
{
	double		NSCI_Fi_G;		//Горизонтальный пеленг ЛВ в ССК
};
//Вертикальный пеленг ЛВ
struct NSCI_BCVM_Fi_V
{
	double		NSCI_Fi_V;		//Вертикальный пеленг ЛВ в ССК
};
//Угол поворота шлема по крену
struct NSCI_BCVM_GAMMA_SH
{
	double		NSCI_GAMMA_SH;	//Угол поворота шлема по крену
};
//Смещение шлема по оси Х ССК
struct NSCI_BCVM_DX
{
	double		NSCI_DX;		//Смещение шлема по оси Х ССК
};
//Смещение шлема по оси Z ССК
struct NSCI_BCVM_DY
{
	double		NSCI_DY;		//Смещение шлема по оси Z ССК
};
//Смещение шлема по оси Y ССК
struct NSCI_BCVM_DZ
{
	double		NSCI_DZ;		//Смещение шлема по оси Y ССК
};

//Номер ВЦ1,2
struct BCVM_VC1_2
{
	int			BCVM_VC1_N;		//Номер ВЦ1
	int			BCVM_VC2_N;		//Номер ВЦ2
};

//Номер ВЦ3,4
struct BCVM_VC3_4
{
	int			BCVM_VC3_N;		//Номер ВЦ3
	int			BCVM_VC4_N;		//Номер ВЦ4
};

//Номер ВЦ5,6
struct BCVM_VC5_6
{
	int			BCVM_VC5_N;		//Номер ВЦ5
	int			BCVM_VC6_N;		//Номер ВЦ6
};

//Номер ВЦ7,8
struct BCVM_VC7_8
{
	int			BCVM_VC7_N;		//Номер ВЦ7
	int			BCVM_VC8_N;		//Номер ВЦ8
};

//Горизонтальный пеленг метки ВЦ1
struct BCVM_NSCI_VC1_FIG
{
	double			BCVM_VC1_FIG;		//Горизонтальный пеленг метки ВЦ1
};

//Вертикальный пеленг метки ВЦ1
struct BCVM_NSCI_VC1_FIV
{
	double			BCVM_VC1_FIV;		//Вертикальный пеленг метки ВЦ1
	int				BCVM_VC1_PRD;		//Признак наличия дальности до ВЦ1
};

//Дальность до ВЦ1
struct BCVM_NSCI_VC1_D
{
	double			BCVM_VC1_D;		//Дальность до ВЦ1
	int				BCVM_VC1_T;		//Тип метки ВЦ1
};

//Ракурс ВЦ на А в ББВ
struct BCVM_NSCI_VC_Q
{
	double			BCVM_VC_Q;		//Ракурс ВЦ на А в ББВ
};


//Горизонтальный пеленг метки ВЦ2
struct BCVM_NSCI_VC2_FIG
{
	double			BCVM_VC2_FIG;		//Горизонтальный пеленг метки ВЦ2
};

//Вертикальный пеленг метки ВЦ2
struct BCVM_NSCI_VC2_FIV
{
	double			BCVM_VC2_FIV;		//Вертикальный пеленг метки ВЦ2
	int				BCVM_VC2_PRD;		//Признак наличия дальности до ВЦ2
};

//Дальность до ВЦ2
struct BCVM_NSCI_VC2_D
{
	double			BCVM_VC2_D;		//Дальность до ВЦ2
	int				BCVM_VC2_T;		//Тип метки ВЦ2
};

//Горизонтальный пеленг метки ВЦ3
struct BCVM_NSCI_VC3_FIG
{
	double			BCVM_VC3_FIG;		//Горизонтальный пеленг метки ВЦ3
};

//Вертикальный пеленг метки ВЦ3
struct BCVM_NSCI_VC3_FIV
{
	double			BCVM_VC3_FIV;		//Вертикальный пеленг метки ВЦ3
	int				BCVM_VC3_PRD;		//Признак наличия дальности до ВЦ3
};

//Дальность до ВЦ3
struct BCVM_NSCI_VC3_D
{
	double			BCVM_VC3_D;		//Дальность до ВЦ3
	int				BCVM_VC3_T;		//Тип метки ВЦ3
};

//Горизонтальный пеленг метки ВЦ4
struct BCVM_NSCI_VC4_FIG
{
	double			BCVM_VC4_FIG;		//Горизонтальный пеленг метки ВЦ4
};

//Вертикальный пеленг метки ВЦ4
struct BCVM_NSCI_VC4_FIV
{
	double			BCVM_VC4_FIV;		//Вертикальный пеленг метки ВЦ4
	int				BCVM_VC4_PRD;		//Признак наличия дальности до ВЦ4
};

//Дальность до ВЦ4
struct BCVM_NSCI_VC4_D
{
	double			BCVM_VC4_D;		//Дальность до ВЦ4
	int				BCVM_VC4_T;		//Тип метки ВЦ4
};

//Горизонтальный пеленг метки ВЦ5
struct BCVM_NSCI_VC5_FIG
{
	double			BCVM_VC5_FIG;		//Горизонтальный пеленг метки ВЦ5
};

//Вертикальный пеленг метки ВЦ5
struct BCVM_NSCI_VC5_FIV
{
	double			BCVM_VC5_FIV;		//Вертикальный пеленг метки ВЦ5
	int				BCVM_VC5_PRD;		//Признак наличия дальности до ВЦ5
};

//Дальность до ВЦ5
struct BCVM_NSCI_VC5_D
{
	double			BCVM_VC5_D;		//Дальность до ВЦ5
	int				BCVM_VC5_T;		//Тип метки ВЦ5
};

//Горизонтальный пеленг метки ВЦ6
struct BCVM_NSCI_VC6_FIG
{
	double			BCVM_VC6_FIG;		//Горизонтальный пеленг метки ВЦ6
};

//Вертикальный пеленг метки ВЦ6
struct BCVM_NSCI_VC6_FIV
{
	double			BCVM_VC6_FIV;		//Вертикальный пеленг метки ВЦ6
	int				BCVM_VC6_PRD;		//Признак наличия дальности до ВЦ6
};

//Дальность до ВЦ6
struct BCVM_NSCI_VC6_D
{
	double			BCVM_VC6_D;		//Дальность до ВЦ6
	int				BCVM_VC6_T;		//Тип метки ВЦ6
};

//Горизонтальный пеленг метки ВЦ7
struct BCVM_NSCI_VC7_FIG
{
	double			BCVM_VC7_FIG;		//Горизонтальный пеленг метки ВЦ7
};

//Вертикальный пеленг метки ВЦ7
struct BCVM_NSCI_VC7_FIV
{
	double			BCVM_VC7_FIV;		//Вертикальный пеленг метки ВЦ7
	int				BCVM_VC7_PRD;		//Признак наличия дальности до ВЦ7
};

//Дальность до ВЦ7
struct BCVM_NSCI_VC7_D
{
	double			BCVM_VC7_D;		//Дальность до ВЦ7
	int				BCVM_VC7_T;		//Тип метки ВЦ7
};

//Горизонтальный пеленг метки ВЦ8
struct BCVM_NSCI_VC8_FIG
{
	double			BCVM_VC8_FIG;		//Горизонтальный пеленг метки ВЦ8
};

//Вертикальный пеленг метки ВЦ8
struct BCVM_NSCI_VC8_FIV
{
	double			BCVM_VC8_FIV;		//Вертикальный пеленг метки ВЦ8
	int				BCVM_VC8_PRD;		//Признак наличия дальности до ВЦ8
};

//Дальность до ВЦ8
struct BCVM_NSCI_VC8_D
{
	double			BCVM_VC8_D;		//Дальность до ВЦ8
	int				BCVM_VC8_T;		//Тип метки ВЦ8
};



//Слово времени 1 формирования координат ЛВ
struct NSCI_BCVM_TIME_1
{
	int		NSCI_HOUR;		//Час измерения координат ЛВ
	int		NSCI_MIN;		//Минута измерения координат ЛВ
};
//Слово времени 2 формирования координат ЛВ
struct NSCI_BCVM_TIME_2
{
	int		NSCI_SEC;		//Секунда измерения координат ЛВ
	int		NSCI_MSEC;		//Миллисекунда измерения координат ЛВ
};


//Подадрес 29. Единое время КБО
struct Subaddres_29_BCVM_GROUP
{
	BCVM_TIME_1	m_BCVM_TIME_1;
	BCVM_TIME_2	m_BCVM_TIME_2;
};

//Подадрес 01. Задаваемые параметры для НСЦИ
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

//Подадрес 02. Задаваемые параметры для НСЦИ
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



//Подадрес 01. Параметры НСЦИ
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
//структура обмена данными с библиотекой MIL
struct DATA_NSCI_TO_VIS 
{
	//Выходные данные
	Subaddres_01_NSCI_BCVM m_Subaddres_01_NSCI_BCVM;
    //Входные данные
	Subaddres_01_BCVM_NSCI m_Subaddres_01_BCVM_NSCI;
	//Входные данные
	Subaddres_02_BCVM_NSCI m_Subaddres_02_BCVM_NSCI;
	//Время
	Subaddres_29_BCVM_GROUP m_Subaddres_29_BCVM_GROUP;

};
#pragma pack(pop)
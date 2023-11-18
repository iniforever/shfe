/*!****************************************************************************
 @note   Copyright (coffee), 2005-2019, Shengli Tech. Co., Ltd.
 @file   efvi_receive_depend.h
 @date   2019/12/25   15:12
 @author gu.jianxiang
 
 @brief   ���ļ�ʾ�������ڻ�lev2��Ϣ

 @note 
******************************************************************************/

#pragma once
#include "efvi_receive_depend.h"

#include <stdint.h>

#define QT_BUFF_COUNT				(8000000)

#pragma pack(push, 1)
struct efh3_2_fut_lev2
{
	unsigned int	m_sequence;				///<�Ự���
	char			m_exchange_id;			///<�г�  0 ��ʾ�н�  1��ʾ����
	char			m_channel_id;			///<ͨ�����
	char			m_symbol[8];			///<��Լ
	uint8_t			m_update_time_h;		///������ʱ��hh
	uint8_t			m_update_time_m;		///������ʱ��mm
	uint8_t			m_update_time_s;		///������ʱ��ss
	uint16_t		m_snap_millisecond;		///<������ʱ��(����)	

	double			m_last_px;				///<���¼�
	uint32_t		m_volume;				///<�����ܳɽ���
	double			m_turnover;				///<�ɽ����
	double			m_open_interest;		///<�ֲ���
	double			m_bid_1_px;				///<�������1��
	uint32_t		m_bid_1_share;			///<��������1��
	double			m_bid_2_px;				///<�������2��
	uint32_t		m_bid_2_share;			///<��������2��
	double			m_bid_3_px;				///<�������3��
	uint32_t		m_bid_3_share;			///<��������3��
	double			m_bid_4_px;				///<�������4��
	uint32_t		m_bid_4_share;			///<��������4��
	double			m_bid_5_px;				///<�������5��
	uint32_t		m_bid_5_share;			///<��������5��

	double			m_ask_1_px;				///<��������1��
	uint32_t		m_ask_1_share;			///<��������1��
	double			m_ask_2_px;				///<��������2��
	uint32_t		m_ask_2_share;			///<��������2��
	double			m_ask_3_px;				///<��������3��
	uint32_t		m_ask_3_share;			///<��������3��
	double			m_ask_4_px;				///<��������4��
	uint32_t		m_ask_4_share;			///<��������4��
	double			m_ask_5_px;				///<��������5��
	uint32_t		m_ask_5_share;			///<��������5��

	uint8_t			m_reserve;
};

#pragma pack(pop)

class udp_quote_fut_lev2
{
public:
	udp_quote_fut_lev2(void);
	~udp_quote_fut_lev2(void);

	bool init( sock_udp_param &shfe );
	void close();
private:
	int sl_parse(ef_filter_spec* fs, const char* ip,  unsigned short port);
	struct pkt_buf* pkt_buf_from_id(struct resources* res, int pkt_buf_i);
	void pkt_buf_free(struct resources* res, struct pkt_buf* pkt_buf);
	void handle_rx(struct resources* res, int pkt_buf_i, int len);
	void handle_rx_discard(struct resources* res, int pkt_buf_i, int len, int discard_type);
	void refill_rx_ring(struct resources* res);

	/// �����߳�
	bool start_recv_thread(); 
	static void* func_work_thread(void* param);
	int on_work_thread();
	void thread_main_loop(struct resources* res);
	/// ��¼��־����
	void write_log(const char* msg);
	/// ��CPU
	bool bind_cpu(int cpu_id, pthread_t thd_id);
	/// ��¼��������
	void log_quote();
private:
	sock_udp_param		m_udp_param;			///<�鲥����
	bool				m_receive_quit_flag;	///<�˳��̵߳ı�־	
	struct resources*	m_res;					///<������Դ

	/// ���������Դ
	long long			m_ll_qt_count;
	efh3_2_fut_lev2		m_qt[QT_BUFF_COUNT];
};


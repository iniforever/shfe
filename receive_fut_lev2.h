/*!****************************************************************************
 @note   Copyright (coffee), 2005-2019, Shengli Tech. Co., Ltd.
 @file   efvi_receive_depend.h
 @date   2019/12/25   15:12
 @author gu.jianxiang
 
 @brief   本文件示例接收期货lev2消息

 @note 
******************************************************************************/

#pragma once
#include "efvi_receive_depend.h"

#include <stdint.h>

#define QT_BUFF_COUNT				(8000000)

#pragma pack(push, 1)
struct efh3_2_fut_lev2
{
	unsigned int	m_sequence;				///<会话编号
	char			m_exchange_id;			///<市场  0 表示中金  1表示上期
	char			m_channel_id;			///<通道编号
	char			m_symbol[8];			///<合约
	uint8_t			m_update_time_h;		///最后更新时间hh
	uint8_t			m_update_time_m;		///最后更新时间mm
	uint8_t			m_update_time_s;		///最后更新时间ss
	uint16_t		m_snap_millisecond;		///<最后更新时间(毫秒)	

	double			m_last_px;				///<最新价
	uint32_t		m_volume;				///<最新总成交量
	double			m_turnover;				///<成交金额
	double			m_open_interest;		///<持仓量
	double			m_bid_1_px;				///<最新买价1档
	uint32_t		m_bid_1_share;			///<最新买量1档
	double			m_bid_2_px;				///<最新买价2档
	uint32_t		m_bid_2_share;			///<最新买量2档
	double			m_bid_3_px;				///<最新买价3档
	uint32_t		m_bid_3_share;			///<最新买量3档
	double			m_bid_4_px;				///<最新买价4档
	uint32_t		m_bid_4_share;			///<最新买量4档
	double			m_bid_5_px;				///<最新买价5档
	uint32_t		m_bid_5_share;			///<最新买量5档

	double			m_ask_1_px;				///<最新卖价1档
	uint32_t		m_ask_1_share;			///<最新卖量1档
	double			m_ask_2_px;				///<最新卖价2档
	uint32_t		m_ask_2_share;			///<最新卖量2档
	double			m_ask_3_px;				///<最新卖价3档
	uint32_t		m_ask_3_share;			///<最新卖量3档
	double			m_ask_4_px;				///<最新卖价4档
	uint32_t		m_ask_4_share;			///<最新卖量4档
	double			m_ask_5_px;				///<最新卖价5档
	uint32_t		m_ask_5_share;			///<最新卖量5档

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

	/// 创建线程
	bool start_recv_thread(); 
	static void* func_work_thread(void* param);
	int on_work_thread();
	void thread_main_loop(struct resources* res);
	/// 记录日志功能
	void write_log(const char* msg);
	/// 绑定CPU
	bool bind_cpu(int cpu_id, pthread_t thd_id);
	/// 记录行情内容
	void log_quote();
private:
	sock_udp_param		m_udp_param;			///<组播参数
	bool				m_receive_quit_flag;	///<退出线程的标志	
	struct resources*	m_res;					///<行情资源

	/// 行情接收资源
	long long			m_ll_qt_count;
	efh3_2_fut_lev2		m_qt[QT_BUFF_COUNT];
};


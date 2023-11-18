/*!****************************************************************************
 @note   Copyright (coffee), 2005-2019, Shengli Tech. Co., Ltd.
 @file   efvi_receive_depend.h
 @date   2019/12/25   15:12
 @author gu.jianxiang
 
 @brief   本文件是示例程序的入口

 @note 
******************************************************************************/

#include "receive_fut_lev1.h"
#include "receive_fut_lev2.h"
#include "receive_opt_lev1.h"
#include "receive_opt_lev2.h"

int main()
{
	/// add by zhou.hu review  2020/4/25  需要接收那个组播通道就实例化那个具体的类型即可

//	udp_quote_fut_lev1* p_qt = new udp_quote_fut_lev1();
	udp_quote_fut_lev2* p_qt = new udp_quote_fut_lev2();
//	udp_quote_opt_lev1* p_qt = new udp_quote_opt_lev1();
//	udp_quote_opt_lev2* p_qt = new udp_quote_opt_lev2();

	if( p_qt == NULL )
	{
		printf("malloc udp receive snap failed.\n");
		return -1;
	}

	sock_udp_param snap_param;

	snap_param.m_i_cpu_id		= 6;
	snap_param.m_multicast_ip	= "233.54.1.102";
	snap_param.m_multicast_port	= 20012;
	snap_param.m_eth_name		= "eth3";


	if( !p_qt->init( snap_param ) )
	{
		printf("lev2 receive init failed.\n");
		return -1;
	}

	while( true )
	{
		printf("[EFH3.2_Demo]:");
		fflush( stdout );

		char buf[1024] = {0};
		fgets(buf, sizeof(buf), stdin);
		int len = strlen(buf);
		if( len <= 0 )
		{
			continue;;
		}
		buf[len - 1] = 0;
		printf("\n");

		if( strcmp( buf, "quit" ) == 0 )
		{
			break;
		}
	}

	p_qt->close();

	delete p_qt;

	p_qt = NULL;

	return 0;
}

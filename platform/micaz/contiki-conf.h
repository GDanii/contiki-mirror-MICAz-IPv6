/*
 * Copyright (c) 2009, University of Colombo School of Computing
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * @(#)$$
 */

/**
 * \file
 *         Configuration for MICAz platform.
 *
 * \author
 *         Kasun Hewage <kasun.ch@gmail.com>
 *         Daniel Gehberger <daniel.gehberger@gmail.com>
 */

/* With these tuned configurations, the rpl-border-router (without the webserver) could be also runned on the MICAz mote.
 * 	The Data memory will be around 90%
 * With more decreased numbers it is possible with the webserver too.
 */

#ifndef __CONTIKI_CONF_H__
#define __CONTIKI_CONF_H__

#define HAVE_STDINT_H
#include "avrdef.h"

#include "platform-conf.h"

/* Logging */
#define LOG_CONF_ENABLED 0

/* The process names are not used to save RAM */
#define PROCESS_CONF_NO_PROCESS_NAMES 1

#define PACKETBUF_CONF_ATTRS_INLINE 1
#define PROCESS_CONF_NUMEVENTS 8
#define PROCESS_CONF_STATS 0
#define CCIF
#define CLIF
#define CC2420_CONF_SYMBOL_LOOP_COUNT 500

/* General network setup */
  #define NETSTACK_CONF_FRAMER		framer_802154
  #define CC2420_CONF_AUTOACK		1
  #define MAC_CONF_CHANNEL_CHECK_RATE	8
  #define CXMAC_CONF_ANNOUNCEMENTS	0

  #ifndef RF_CHANNEL
  #define RF_CHANNEL	26
  #endif /* RF_CHANNEL */
  
  #define UIP_CONF_LLH_LEN		0
  #define UIP_CONF_ICMP_DEST_UNREACH	1
  #define UIP_CONF_DHCP_LIGHT
  #define UIP_CONF_BROADCAST		1
  #define UIP_CONF_TCP_SPLIT		0
  
  /* For TCP */
  #define UIP_CONF_TCP_MSS		48
  #define UIP_CONF_MAX_CONNECTIONS	4 //Original: 10, 44 bytes each
  #define UIP_CONF_MAX_LISTENPORTS	10 //Original: 20, 6 bytes each
  
  /* For UDP */
  #define UIP_CONF_UDP_CONNS		5 //Original: 10, 25 bytes each

  
#if UIP_CONF_IPV6
  /* Network setup for IPv6 */
  #define NETSTACK_CONF_NETWORK	sicslowpan_driver
  //#define NETSTACK_CONF_MAC	csma_driver	//+ ~130 bytes, Mainly: QUEUEBUF_CONF_NUM*11+CSMA_CONF_MAX_NEIGHBOR_QUEUES(2*33)
  #define NETSTACK_CONF_MAC	nullmac_driver
  //#define NETSTACK_CONF_RDC	nullrdc_driver
  #define NETSTACK_CONF_RDC	sicslowmac_driver 

  #define RIME_CONF_NO_POLITE_ANNOUCEMENTS 0
  
  /* Addresses, Sizes and Interfaces */
  #define RIMEADDR_CONF_SIZE		8
  #define UIP_CONF_LL_802154		1
  #define UIP_CONF_NETIF_MAX_ADDRESSES	3
  
  /* TCP, UDP, ICMP */
  #define UIP_CONF_TCP			0 //TCP OFF!
  #define UIP_CONF_UDP			1
  #define UIP_CONF_UDP_CHECKSUMS	1

  /* ND and DS */
  #define UIP_CONF_ND6_SEND_RA	0
  #define UIP_CONF_IP_FORWARD	0
  
  #define UIP_CONF_ND6_REACHABLE_TIME	600000
  #define UIP_CONF_ND6_RETRANS_TIMER	10000
  
  #define UIP_CONF_DS6_NBR_NBU		3 //Original: 4, 46 bytes each
  #define UIP_CONF_DS6_ROUTE_NBU	3 //Original: 4, 46 bytes each
  #define UIP_CONF_DS6_DEFRT_NBU	1 //Original: 2, 26 bytes each
  #define UIP_CONF_DS6_PREFIX_NBU	2 //Original: 2, 42 bytes each
  
  /* uIP */
  #define UIP_CONF_BUFFER_SIZE		240 //Original: 240 bytes, It is counted for UIP and RX buffer too!
  #define UIP_CONF_IPV6_QUEUE_PKT	0
  #define UIP_CONF_IPV6_CHECKS		1
  #define UIP_CONF_IPV6_REASSEMBLY	0
  
  /* sicslowpan */
  #define SICSLOWPAN_CONF_COMPRESSION		SICSLOWPAN_COMPRESSION_HC06
  #define SICSLOWPAN_CONF_MAXAGE		8
  #define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS	2 //Original: 1, 10 bytes each
  
  /* RPL */
  #define UIP_CONF_ROUTER		1
  #define RPL_CONF_MAX_PARENTS_PER_DAG	4//Original: 8
  #define RPL_CONF_MAX_DAG_PER_INSTANCE	1 //Original: 2
    //RPL_CONF_MAX_PARENTS_PER_DAG*RPL_CONF_MAX_DAG_PER_INSTANCE*RPL_MAX_INSTANCES(1)*32 bytes
  
  /* Rime */
  #define QUEUEBUF_CONF_NUM          	4 //Original: 8, 210 bytes each
  #define QUEUEBUF_CONF_REF_NUM		2 //Original: 2, 53 bytes each
  #define NEIGHBOR_CONF_MAX_NEIGHBORS	8 //Original: 12, 14 bytes each

#else /* WITH_UIP6 */
/* Network setup for non-IPv6 */
  #define NETSTACK_CONF_NETWORK rime_driver
  #define NETSTACK_CONF_RDC     cxmac_driver
  #define NETSTACK_CONF_MAC     csma_driver
  //#define NETSTACK_CONF_MAC     nullmac_driver

  #define COLLECT_CONF_ANNOUNCEMENTS       1
  #define RIME_CONF_NO_POLITE_ANNOUCEMENTS 1
  #define CXMAC_CONF_COMPOWER              1

  #define COLLECT_NEIGHBOR_CONF_MAX_NEIGHBORS      32
  
  #define UIP_CONF_IP_FORWARD	1
  #define UIP_CONF_BUFFER_SIZE	128
  #define QUEUEBUF_CONF_NUM	8
  #define UIP_CONF_FWCACHE_SIZE	15
  #define AODV_COMPLIANCE
#endif /* WITH_UIP6 */

/* include the project config */
/* PROJECT_CONF_H might be defined in the project Makefile */
#ifdef PROJECT_CONF_H
#include PROJECT_CONF_H
#endif /* PROJECT_CONF_H */

typedef unsigned short uip_stats_t;
typedef unsigned long off_t;


#endif /* __CONTIKI_CONF_H__ */

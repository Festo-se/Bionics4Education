/* 
 * Esp32 DNS Hijacking Server.
 * Copyright Alija Bobija, 2019.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <lwip/netdb.h>

#define DNS_HIJACK_SRV_HEADER_SIZE           12
#define DNS_HIJACK_SRV_QUESTION_MAX_LENGTH   50

typedef struct dns_hijack_srv_handle_t {
	TaskHandle_t task_handle;
	int sockfd;
	ip4_addr_t resolve_ip;
} dns_hijack_srv_handle_t;

typedef struct __attribute__((packed)) dns_header_t {
	uint16_t ID;
	uint8_t  RD       :1;
	uint8_t  TC       :1;
	uint8_t  AA       :1;
	uint8_t  OPCODE   :4;
	uint8_t  QR       :1;
	uint8_t  RCODE    :4;
	uint8_t  Z        :3;
	uint8_t  RA       :1;
	uint16_t QDCOUNT;
	uint16_t ANCOUNT;
	uint16_t NSCOUNT;
	uint16_t ARCOUNT;
} dns_header_t;

typedef struct __attribute__((packed)) dns_hijack_answer_t {
	uint16_t NAME;
	uint16_t TYPE;
	uint16_t CLASS;
	uint32_t TTL;
	uint16_t RDLENGTH;
	uint32_t RDATA;
} dns_hijack_answer_t;

esp_err_t dns_hijack_srv_start(const ip4_addr_t resolve_ip_addr);
esp_err_t dns_hijack_srv_stop();

#ifdef __cplusplus
}
#endif
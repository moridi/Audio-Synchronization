#ifndef CONFIG_H_
#define CONFIG_H_

/*
 * A RTP server 
 *  sends the output of alsasrc as opus encoded RTP on port 5002, RTCP is sent on
 *  port 5003.
 *  the receiver RTCP reports are received on port 5007
 *
 * .------------.   .---------.   .--------.     .-------.   .-------.      .-----------------.     .-------.
 * |audiotestsrc|   |Converter|   |Resample|     |OpusEnc|   |OpusPay|      | RtpBin          |     |UdpSink|  RTP
 * |         src->sink      src->sink    src->sink    src->sink    src->send_rtp   send_rtp->sink   |    port=5002
 * '------------'   '---------'   '--------'     '-------'   '-------'      |                 |     '-------'
 *                                                                          |                 |      
 *                                                                          |                 |     .-------.
 *                                                                          |                 |     |UdpSink|  RTCP
 *                                                                          |        send_rtcp->sink        | port=5003
 *                                                         .-------.        |                 |     '-------' 
 *                                                 RTCP    |UdpSrc |        |                 |               
 *                                             port=5007   |    src->recv_rtcp                |                       
 *                                                         '-------'        '-----------------'              
 */                           

/* change this to send the RTP data and RTCP to another host */

// char FIRST_CLIENT_IP[] = "192.168.1.8";
char FIRST_CLIENT_IP[] = "127.0.0.1";
char SECOND_CLINET_IP[] = "172.20.10.3";

char* DEST_HOST[] = {FIRST_CLIENT_IP, SECOND_CLINET_IP};

#define AUDIO_SRC  "audiotestsrc"

/* the encoder and payloader elements */
#define AUDIO_ENC  "opusenc"
#define AUDIO_PAY  "rtpopuspay"

#define RTP_PORT_IDX 0
#define RTCP_SEND_PORT_IDX 1
#define RTCP_RCV_PORT_IDX 2

#define NUMBER_OF_CLIENTS 2

int FIRST_CLIENT_PORTS[] = {5002, 5003, 5007};
int SECOND_CLIENT_PORTS[] = {5012, 5013, 5017};
int* CLIENTS_PORTS[] = {FIRST_CLIENT_PORTS, SECOND_CLIENT_PORTS};
#endif
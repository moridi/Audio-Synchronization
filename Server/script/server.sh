#!/bin/sh
#
# A RTP server 
#  sends the output of alsasrc as opus encoded RTP on port 5002, RTCP is sent on
#  port 5003. The destination is 127.0.0.1.
#  the receiver RTCP reports are received on port 5007
#
# .------------.   .-------.   .-------.      .-----------------.     .-------.
# |audiotestsrc|   |opusenc|   |opuspay|      | rtpbin          |     |udpsink|  RTP
# |         src->sink   src->sink    src->send_rtp   send_rtp->sink   |    port=5002
# '------------'   '-------'   '-------'      |                 |     '-------'
#                                             |                 |      
#                                             |                 |     .-------.
#                                             |                 |     |udpsink|  RTCP
#                                             |        send_rtcp->sink        | port=5003
#                              .-------.      |                 |     '-------' sync=false
#                      RTCP    |udpsrc |      |                 |               async=false
#                  port=5007   |    src->recv_rtcp              |                       
#                              '-------'      '-----------------'              
#

# change this to send the RTP data and RTCP to another host
DEST=127.0.0.1

AELEM=audiotestsrc
# AELEM=jackaudiosrc

# OPUS encode from an the source
ASOURCE="$AELEM wave=8 is-live=TRUE ! audioconvert ! audioresample"
AENC="opusenc  bitrate=256000 ! rtpopuspay"

gst-launch-1.0 -v rtpbin name=rtpbin \
     $ASOURCE ! $AENC ! rtpbin.send_rtp_sink_0  \
     $ASOURCE ! $AENC ! rtpbin.send_rtp_sink_1  \
            rtpbin.send_rtp_src_0 ! udpsink port=5002 host=$DEST                      \
            rtpbin.send_rtp_src_1 ! udpsink port=5012 host=$DEST                      \
            rtpbin.send_rtcp_src_0 ! udpsink port=5003 host=$DEST sync=false async=false \
            udpsrc port=5007 ! rtpbin.recv_rtcp_sink_0
            rtpbin.send_rtcp_src_1 ! udpsink port=5013 host=$DEST sync=false async=false \
            udpsrc port=5017 ! rtpbin.recv_rtcp_sink_1
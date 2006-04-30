#ifndef _GPXE_TCP_H
#define _GPXE_TCP_H

/** @file
 *
 * TCP protocol
 *
 * This file defines the gPXE TCP API.
 *
 */

#include <stddef.h>
#include <gpxe/in.h>

struct tcp_connection;

/**
 * TCP operations
 *
 */
struct tcp_operations {
	/*
	 * Connection closed
	 *
	 * @v conn	TCP connection
	 * @v status	Error code, if any
	 *
	 * This is called when the connection is closed for any
	 * reason, including timeouts or aborts.  The status code
	 * contains the negative error number, if the closure is due
	 * to an error.
	 *
	 * Note that acked() and newdata() may be called after
	 * closed(), if the packet containing the FIN also
	 * acknowledged data or contained new data.  Note also that
	 * connected() may not have been called before closed(), if
	 * the close is due to an error.
	 */
	void ( * closed ) ( struct tcp_connection *conn, int status );
	/**
	 * Connection established (SYNACK received)
	 *
	 * @v conn	TCP connection
	 */
	void ( * connected ) ( struct tcp_connection *conn );
	/**
	 * Data acknowledged
	 *
	 * @v conn	TCP connection
	 * @v len	Length of acknowledged data
	 *
	 * @c len is guaranteed to not exceed the outstanding amount
	 * of unacknowledged data.
	 */
	void ( * acked ) ( struct tcp_connection *conn, size_t len );
	/**
	 * New data received
	 *
	 * @v conn	TCP connection
	 * @v data	Data
	 * @v len	Length of data
	 */
	void ( * newdata ) ( struct tcp_connection *conn,
			     void *data, size_t len );
	/**
	 * Transmit data
	 *
	 * @v conn	TCP connection
	 *
	 * The application should transmit whatever it currently wants
	 * to send using tcp_send().  If retransmissions are required,
	 * senddata() will be called again and the application must
	 * regenerate the data.  The easiest way to implement this is
	 * to ensure that senddata() never changes the application's
	 * state.
	 */
	void ( * senddata ) ( struct tcp_connection *conn );
};

/**
 * A TCP connection
 *
 */
struct tcp_connection {
	/** Address of the remote end of the connection */
	struct sockaddr_in sin;
	/** Operations table for this connection */
	struct tcp_operations *tcp_op;
};

extern void *tcp_buffer;
extern size_t tcp_buflen;
extern void tcp_connect ( struct tcp_connection *conn );
extern void tcp_send ( struct tcp_connection *conn, const void *data,
		       size_t len );
extern void tcp_close ( struct tcp_connection *conn );

#endif /* _GPXE_TCP_H */

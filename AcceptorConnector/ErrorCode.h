#pragma once

#if _MSC_VER
/*
//  accept return error code
        case WSANOTINITIALISED:
        case WSAENETDOWN:
        case WSAEACCES:
        case WSAEADDRINUSE:     // need SO_REUSEADD
        case WSAEADDRNOTAVAIL:
        case WSAEFAULT:
        case WSAEINPROGRESS:
        case WSAEINVAL:
        case WSAENOBUFS:
        case WSAENOTSOCK:

//  bind return error code
        case WSANOTINITIALISED:
        case WSAECONNRESET:
        case WSAEFAULT:
        case WSAEINTR:
        case WSAEINPROGRESS:
        case WSAEMFILE:         // too many sockets (file description)
        case WSAENETDOWN:
        case WSAENOBUFS:
        case WSAENOTSOCK:
        case WSAEOPNOTSUPP:
        case WSAEWOULDBLOCK:

// shutdown error code
    case WSAECONNABORTED:
    case WSAECONNRESET:
    case WSAEINPROGRESS:
    case WSAEINVAL:
    case WSAENETDOWN:
    case WSAENOTCONN:
    case WSAENOTSOCK:
    case WSANOTINITIALISED:
*/
#else
/*
// bind ret error code
EADDRINUSE The specified address is already in use.
EADDRNOTAVAIL The specified address is not available from the local machine.
EAFNOSUPPORT The specified address is not a valid address for the address family of the specified socket.
EALREADY An assignment request is already in progress for the specified socket.
EBADF  The socket argument is not a valid file descriptor.
EINPROGRESS O_NONBLOCK is set for the file descriptor for the socket and the assignment cannot be immediately performed; the assignment shall be performed asynchronously.
EINVAL The socket is already bound to an address, and the protocol does not support binding to a new address; or the socket has been shut down.
ENOBUFS Insufficient resources were available to complete the call.
ENOTSOCK The socket argument does not refer to a socket.
EOPNOTSUPP The socket type of the specified socket does not support binding to an address.

// shutdown error code
EBADF  The socket argument is not a valid file descriptor.
EINVAL The how argument is invalid.
ENOTCONN The socket is not connected.
ENOTSOCK The socket argument does not refer to a socket.

// listen error code
EBADF  The socket argument is not a valid file descriptor.
EDESTADDRREQ The socket is not bound to a local address, and the protocol does not support listening on an unbound socket.
EINVAL The socket is already connected.
ENOTSOCK The socket argument does not refer to a socket.
EOPNOTSUPP The socket protocol does not support listen().

The listen() function may fail if:

EACCES The calling process does not have appropriate privileges.
EINVAL The socket has been shut down.
ENOBUFS Insufficient resources are available in the system to complete the call.

// socket error code
EAFNOSUPPORT The implementation does not support the specified address family.
EMFILE All file descriptors available to the process are currently open.
ENFILE No more file descriptors are available for the system.
EPROTONOSUPPORT The protocol is not supported by the address family, or the protocol is not supported by the implementation.
EPROTOTYPE The socket type is not supported by the protocol.

The socket() function may fail if:

EACCES The process does not have appropriate privileges.
ENOBUFS Insufficient resources were available in the system to perform the operation.
ENOMEM Insufficient memory was available to fulfill the request.
*/
#endif // _MSC_VER

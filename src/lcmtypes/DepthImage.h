// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include <stdint.h>
#include <stdlib.h>
#include <lcm/lcm_coretypes.h>
#include <lcm/lcm.h>

#ifndef _DepthImage_h
#define _DepthImage_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DepthImage DepthImage;
struct _DepthImage
{
    int64_t    utime;
    int32_t    width;
    int32_t    height;
    int32_t    line_stride;
    int32_t    bytes_per_pixel;
    int32_t    num_bytes;
    uint8_t    *pixel_data;
    float      meters_per_unit;
};

/**
 * Create a deep copy of a DepthImage.
 * When no longer needed, destroy it with DepthImage_destroy()
 */
DepthImage* DepthImage_copy(const DepthImage* to_copy);

/**
 * Destroy an instance of DepthImage created by DepthImage_copy()
 */
void DepthImage_destroy(DepthImage* to_destroy);

/**
 * Identifies a single subscription.  This is an opaque data type.
 */
typedef struct _DepthImage_subscription_t DepthImage_subscription_t;

/**
 * Prototype for a callback function invoked when a message of type
 * DepthImage is received.
 */
typedef void(*DepthImage_handler_t)(const lcm_recv_buf_t *rbuf,
             const char *channel, const DepthImage *msg, void *userdata);

/**
 * Publish a message of type DepthImage using LCM.
 *
 * @param lcm The LCM instance to publish with.
 * @param channel The channel to publish on.
 * @param msg The message to publish.
 * @return 0 on success, <0 on error.  Success means LCM has transferred
 * responsibility of the message data to the OS.
 */
int DepthImage_publish(lcm_t *lcm, const char *channel, const DepthImage *msg);

/**
 * Subscribe to messages of type DepthImage using LCM.
 *
 * @param lcm The LCM instance to subscribe with.
 * @param channel The channel to subscribe to.
 * @param handler The callback function invoked by LCM when a message is received.
 *                This function is invoked by LCM during calls to lcm_handle() and
 *                lcm_handle_timeout().
 * @param userdata An opaque pointer passed to @p handler when it is invoked.
 * @return 0 on success, <0 if an error occured
 */
DepthImage_subscription_t* DepthImage_subscribe(lcm_t *lcm, const char *channel, DepthImage_handler_t handler, void *userdata);

/**
 * Removes and destroys a subscription created by DepthImage_subscribe()
 */
int DepthImage_unsubscribe(lcm_t *lcm, DepthImage_subscription_t* hid);

/**
 * Sets the queue capacity for a subscription.
 * Some LCM providers (e.g., the default multicast provider) are implemented
 * using a background receive thread that constantly revceives messages from
 * the network.  As these messages are received, they are buffered on
 * per-subscription queues until dispatched by lcm_handle().  This function
 * how many messages are queued before dropping messages.
 *
 * @param subs the subscription to modify.
 * @param num_messages The maximum number of messages to queue
 *  on the subscription.
 * @return 0 on success, <0 if an error occured
 */
int DepthImage_subscription_set_queue_capacity(DepthImage_subscription_t* subs,
                              int num_messages);

/**
 * Encode a message of type DepthImage into binary form.
 *
 * @param buf The output buffer.
 * @param offset Encoding starts at this byte offset into @p buf.
 * @param maxlen Maximum number of bytes to write.  This should generally
 *               be equal to DepthImage_encoded_size().
 * @param msg The message to encode.
 * @return The number of bytes encoded, or <0 if an error occured.
 */
int DepthImage_encode(void *buf, int offset, int maxlen, const DepthImage *p);

/**
 * Decode a message of type DepthImage from binary form.
 * When decoding messages containing strings or variable-length arrays, this
 * function may allocate memory.  When finished with the decoded message,
 * release allocated resources with DepthImage_decode_cleanup().
 *
 * @param buf The buffer containing the encoded message
 * @param offset The byte offset into @p buf where the encoded message starts.
 * @param maxlen The maximum number of bytes to read while decoding.
 * @param msg Output parameter where the decoded message is stored
 * @return The number of bytes decoded, or <0 if an error occured.
 */
int DepthImage_decode(const void *buf, int offset, int maxlen, DepthImage *msg);

/**
 * Release resources allocated by DepthImage_decode()
 * @return 0
 */
int DepthImage_decode_cleanup(DepthImage *p);

/**
 * Check how many bytes are required to encode a message of type DepthImage
 */
int DepthImage_encoded_size(const DepthImage *p);

// LCM support functions. Users should not call these
int64_t __DepthImage_get_hash(void);
uint64_t __DepthImage_hash_recursive(const __lcm_hash_ptr *p);
int     __DepthImage_encode_array(void *buf, int offset, int maxlen, const DepthImage *p, int elements);
int     __DepthImage_decode_array(const void *buf, int offset, int maxlen, DepthImage *p, int elements);
int     __DepthImage_decode_array_cleanup(DepthImage *p, int elements);
int     __DepthImage_encoded_array_size(const DepthImage *p, int elements);
int     __DepthImage_clone_array(const DepthImage *p, DepthImage *q, int elements);

#ifdef __cplusplus
}
#endif

#endif

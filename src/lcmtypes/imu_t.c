// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include <string.h>
#include "imu_t.h"

static int __imu_t_hash_computed;
static uint64_t __imu_t_hash;

uint64_t __imu_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __imu_t_get_hash)
            return 0;

    __lcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = __imu_t_get_hash;
    (void) cp;

    uint64_t hash = (uint64_t)0x936fa8e9ddd37b37LL
         + __int64_t_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __imu_t_get_hash(void)
{
    if (!__imu_t_hash_computed) {
        __imu_t_hash = (int64_t)__imu_t_hash_recursive(NULL);
        __imu_t_hash_computed = 1;
    }

    return __imu_t_hash;
}

int __imu_t_encode_array(void *buf, int offset, int maxlen, const imu_t *p, int elements)
{
    int pos = 0, element;
    int thislen;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].utime), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, p[element].gyro, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        { int a;
        for (a = 0; a < 3; a++) {
            thislen = __float_encode_array(buf, offset + pos, maxlen - pos, p[element].gyro_covariance[a], 3);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, p[element].accel, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        { int a;
        for (a = 0; a < 3; a++) {
            thislen = __float_encode_array(buf, offset + pos, maxlen - pos, p[element].accel_covariance[a], 3);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, p[element].orientation, 4);
        if (thislen < 0) return thislen; else pos += thislen;

        { int a;
        for (a = 0; a < 4; a++) {
            thislen = __float_encode_array(buf, offset + pos, maxlen - pos, p[element].orientation_covariance[a], 4);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

    }
    return pos;
}

int imu_t_encode(void *buf, int offset, int maxlen, const imu_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __imu_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __imu_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __imu_t_encoded_array_size(const imu_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __int64_t_encoded_array_size(&(p[element].utime), 1);

        size += __float_encoded_array_size(p[element].gyro, 3);

        { int a;
        for (a = 0; a < 3; a++) {
            size += __float_encoded_array_size(p[element].gyro_covariance[a], 3);
        }
        }

        size += __float_encoded_array_size(p[element].accel, 3);

        { int a;
        for (a = 0; a < 3; a++) {
            size += __float_encoded_array_size(p[element].accel_covariance[a], 3);
        }
        }

        size += __float_encoded_array_size(p[element].orientation, 4);

        { int a;
        for (a = 0; a < 4; a++) {
            size += __float_encoded_array_size(p[element].orientation_covariance[a], 4);
        }
        }

    }
    return size;
}

int imu_t_encoded_size(const imu_t *p)
{
    return 8 + __imu_t_encoded_array_size(p, 1);
}

int __imu_t_decode_array(const void *buf, int offset, int maxlen, imu_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].utime), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, p[element].gyro, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        { int a;
        for (a = 0; a < 3; a++) {
            thislen = __float_decode_array(buf, offset + pos, maxlen - pos, p[element].gyro_covariance[a], 3);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, p[element].accel, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        { int a;
        for (a = 0; a < 3; a++) {
            thislen = __float_decode_array(buf, offset + pos, maxlen - pos, p[element].accel_covariance[a], 3);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, p[element].orientation, 4);
        if (thislen < 0) return thislen; else pos += thislen;

        { int a;
        for (a = 0; a < 4; a++) {
            thislen = __float_decode_array(buf, offset + pos, maxlen - pos, p[element].orientation_covariance[a], 4);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

    }
    return pos;
}

int __imu_t_decode_array_cleanup(imu_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_decode_array_cleanup(&(p[element].utime), 1);

        __float_decode_array_cleanup(p[element].gyro, 3);

        { int a;
        for (a = 0; a < 3; a++) {
            __float_decode_array_cleanup(p[element].gyro_covariance[a], 3);
        }
        }

        __float_decode_array_cleanup(p[element].accel, 3);

        { int a;
        for (a = 0; a < 3; a++) {
            __float_decode_array_cleanup(p[element].accel_covariance[a], 3);
        }
        }

        __float_decode_array_cleanup(p[element].orientation, 4);

        { int a;
        for (a = 0; a < 4; a++) {
            __float_decode_array_cleanup(p[element].orientation_covariance[a], 4);
        }
        }

    }
    return 0;
}

int imu_t_decode(const void *buf, int offset, int maxlen, imu_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __imu_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __imu_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int imu_t_decode_cleanup(imu_t *p)
{
    return __imu_t_decode_array_cleanup(p, 1);
}

int __imu_t_clone_array(const imu_t *p, imu_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_clone_array(&(p[element].utime), &(q[element].utime), 1);

        __float_clone_array(p[element].gyro, q[element].gyro, 3);

        { int a;
        for (a = 0; a < 3; a++) {
            __float_clone_array(p[element].gyro_covariance[a], q[element].gyro_covariance[a], 3);
        }
        }

        __float_clone_array(p[element].accel, q[element].accel, 3);

        { int a;
        for (a = 0; a < 3; a++) {
            __float_clone_array(p[element].accel_covariance[a], q[element].accel_covariance[a], 3);
        }
        }

        __float_clone_array(p[element].orientation, q[element].orientation, 4);

        { int a;
        for (a = 0; a < 4; a++) {
            __float_clone_array(p[element].orientation_covariance[a], q[element].orientation_covariance[a], 4);
        }
        }

    }
    return 0;
}

imu_t *imu_t_copy(const imu_t *p)
{
    imu_t *q = (imu_t*) malloc(sizeof(imu_t));
    __imu_t_clone_array(p, q, 1);
    return q;
}

void imu_t_destroy(imu_t *p)
{
    __imu_t_decode_array_cleanup(p, 1);
    free(p);
}

int imu_t_publish(lcm_t *lc, const char *channel, const imu_t *p)
{
      int max_data_size = imu_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = imu_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _imu_t_subscription_t {
    imu_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void imu_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    imu_t p;
    memset(&p, 0, sizeof(imu_t));
    status = imu_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding imu_t!!!\n", status);
        return;
    }

    imu_t_subscription_t *h = (imu_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    imu_t_decode_cleanup (&p);
}

imu_t_subscription_t* imu_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    imu_t_handler_t f, void *userdata)
{
    imu_t_subscription_t *n = (imu_t_subscription_t*)
                       malloc(sizeof(imu_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 imu_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg imu_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int imu_t_subscription_set_queue_capacity (imu_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int imu_t_unsubscribe(lcm_t *lcm, imu_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe imu_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}


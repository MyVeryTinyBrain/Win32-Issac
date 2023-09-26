#pragma once
#ifndef __ExecutionOrder_h__
#define __ExecutionOrder_h__

#include <limits.h>

#define EX_ORDER_TYPE			int
#define EX_ORDER_MIN			INT_MIN
#define EX_ORDER_MAX			INT_MAX
#define EX_ORDER_DEFAULT		0

#define EX_ORDER_CAMERA2D		(-100)
#define EX_ORDER_ANIMATOR		(-99)
#define EX_ORDER_RENDERER		(99)
#define EX_ORDER_COLLIDER2D		(10000)
#define EX_ORDER_BODY2D			(10001)

#endif

//* SPDX-License-Identifier: LGPL-2.0-or-later
/*
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors: Damien Le Moal (damien.lemoal@wdc.com)
 *	    Ting Yao <tingyao@hust.edu.cn>
 */
#include "zbd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
 * Log level.
 */
__thread int zbd_log_level = ZBD_LOG_NONE;

void zbd_set_log_level(enum zbd_log_level level)
{
	switch (level) {
	case ZBD_LOG_NONE:
	case ZBD_LOG_ERROR:
	case ZBD_LOG_DEBUG:
		zbd_log_level = level;
		break;
	default:
		fprintf(stderr, "libzbd: Invalid log level %d\n",
			level);
		break;
	}
}

/*
 * To handle string conversions.
 */
struct zbd_str {
	unsigned int	val;
	const char	*str;
	const char	*str_short;
};

static const char *zbd_get_str(struct zbd_str *str, unsigned int val, bool s)
{
	unsigned int i = 0;

	while (str[i].val != UINT_MAX) {
		if (str[i].val == val)
			break;
		i++;
	}

	if (s)
		return str[i].str_short;

	return str[i].str;
}

static struct zbd_str zbd_dm_str[] = {
	{ ZBD_DM_HOST_MANAGED,	"host-managed",	"HM"	},
	{ ZBD_DM_HOST_AWARE,	"host-aware",	"HA"	},
	{ ZBD_DM_NOT_ZONED,	"not-zoned",	"NZ"	},
	{ UINT_MAX,		"unknown",	"??"	},
};

/**
 * zbd_device_model_str - Returns a device zone model name
 */
const char *zbd_device_model_str(enum zbd_dev_model model, bool s)
{
	return zbd_get_str(zbd_dm_str, model, s);
}

static struct zbd_str zbd_ztype_str[] = {
	{ BLK_ZONE_TYPE_CONVENTIONAL,	"conventional",		"cnv"	},
	{ BLK_ZONE_TYPE_SEQWRITE_REQ,	"seq-write-required",	"swr"	},
	{ BLK_ZONE_TYPE_SEQWRITE_PREF,	"seq-write-preferred",	"swp"	},
	{ UINT_MAX,			"unkown",		"???"	}
};

/**
 * zbd_zone_type_str - returns a string describing a zone type
 */
const char *zbd_zone_type_str(struct blk_zone *z, bool s)
{
	return zbd_get_str(zbd_ztype_str, z->type, s);
}

static struct zbd_str zbd_zcond_str[] = {
	{ BLK_ZONE_COND_NOT_WP,		"not-write-pointer",	"nw"	},
	{ BLK_ZONE_COND_EMPTY,		"empty",		"em"	},
	{ BLK_ZONE_COND_FULL,		"full",			"fu"	},
	{ BLK_ZONE_COND_IMP_OPEN,	"open-implicit",	"oi"	},
	{ BLK_ZONE_COND_EXP_OPEN,	"open-explicit",	"oe"	},
	{ BLK_ZONE_COND_CLOSED,		"closed",		"cl"	},
	{ BLK_ZONE_COND_READONLY,	"read-only",		"ro"	},
	{ BLK_ZONE_COND_OFFLINE,	"offline",		"ol"	},
	{ UINT_MAX,			"unkown",		"??"	}
};
/**
 * zbd_zone_cond_str - Returns a string describing a zone condition
 */
const char *zbd_zone_cond_str(struct blk_zone *z, bool s)
{
	return zbd_get_str(zbd_zcond_str, z->cond, s);
}

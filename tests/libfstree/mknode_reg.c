/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * mknode_reg.c
 *
 * Copyright (C) 2019 David Oberhollenzer <goliath@infraroot.at>
 */
#include "config.h"

#include "fstree.h"
#include "util/test.h"

int main(int argc, char **argv)
{
	tree_node_t *node;
	struct stat sb;
	fstree_t fs;
	(void)argc; (void)argv;

	memset(&fs, 0, sizeof(fs));

	memset(&sb, 0, sizeof(sb));
	sb.st_mode = S_IFREG | 0654;
	sb.st_uid = 123;
	sb.st_gid = 456;
	sb.st_rdev = 789;
	sb.st_size = 4096;

	node = fstree_mknode(NULL, "filename", 8, "input", &sb);
	TEST_EQUAL_UI(node->uid, sb.st_uid);
	TEST_EQUAL_UI(node->gid, sb.st_gid);
	TEST_EQUAL_UI(node->mode, sb.st_mode);
	TEST_NULL(node->parent);
	TEST_EQUAL_UI(node->link_count, 1);
	TEST_ASSERT((char *)node->name >= (char *)node->payload);
	TEST_ASSERT(node->data.file.input_file >= (char *)node->payload);
	TEST_ASSERT(node->data.file.input_file >= node->name + 8);
	TEST_STR_EQUAL(node->name, "filename");
	TEST_STR_EQUAL(node->data.file.input_file, "input");
	free(node);

	return EXIT_SUCCESS;
}

// SPDX-License-Identifier: GPL-2.0
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/fuse.h>
#include<linux/err.h>
#include<linux/errno.h>
#include<linux/file.h>
#include<linux/fcntl.h>
#include<linux/uaccess.h>
#include <linux/buffer_head.h>

char * input_path = 0;
static struct file * fp = NULL;

module_param(input_path, charp, S_IRUGO);

static int openFile(char *path)
{
	int fsize = 0;
	int err = 0;
	const char *name;
	unsigned long ino = 0;
	unsigned long bn = 0;
	sector_t block = 0;

	struct inode *inode;
	struct buffer_head *bh;
	struct super_block *sb;

	pr_info("volatile: openFile reached with %s\n", path);

	fp = filp_open(path, O_RDONLY, 0);
	if (!fp || IS_ERR(fp)) {
		pr_info("volatile: File open failed! %ld\n", PTR_ERR(fp));
		err = (fp) ? PTR_ERR(fp) : -EIO;
        fp = NULL;
		return err;
	} else {
		pr_info("volatile: File opened successfully!!!!");
	}

	if (fp != NULL) {
		inode = fp->f_path.dentry->d_inode;
	}

	pr_info("volatile: File opened: %lld bytes\n", i_size_read(inode));
	pr_info("volatile: File opened: %lu inode\n", inode->i_ino);

	sb = inode->i_sb;
    block = bmap(inode, 0);
    if (!block) {
        pr_info("volatile: Unable to map physical block\n");
        filp_close(fp, NULL);
        // return -EINVAL;
    }

    pr_info("volatile: Physical Block: %llu\n", (unsigned long long)block);

	// block = inode->i_mapping->host->i_ino / (4096 / sb->s_blocksize);
    bh = sb_bread(sb, block);
    if (!bh) {
        printk(KERN_ERR "Cannot read the block\n");
        filp_close(fp, NULL);
        return -EIO;
    }

    pr_info("volatile: Physical address: %llu\n", (unsigned long long)bh->b_blocknr * 4096);

	brelse(bh);

	filp_close(fp, NULL);
	return 0;
}

static int __init volative_init(void)
{
    if(!input_path) {
        pr_info("volatile: No path parameter specified");
        return -EINVAL;
	}
	pr_info("volatile: Module Initialised\n");
	pr_info("volatile: Input param is %s\n", input_path);

	openFile(input_path);
	return 0;
}

static void __exit volative_exit(void)
{
	pr_info("volatile: GoodBye World\n");
}

module_init(volative_init);
module_exit(volative_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saalim Quadri <danascape@gmail.com>");
MODULE_DESCRIPTION("Dump Non-Volatile Memory");

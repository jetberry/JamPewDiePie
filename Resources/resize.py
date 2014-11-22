#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os, shutil, Image

'''
"IOError: decoder zip not available" workaround for osx Yosemite:
sudo pip uninstall PIL
brew install zlib
brew link --force zlib
sudo pip install PIL --allow-external PIL --allow-unverified PIL
sudo pip install pillow
'''

RES_100 = 'ipadhd'
RES_50 = 'hd'
RES_25 = 'sd'
SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
RES_100_DIR = SCRIPT_DIR + '/' + RES_100
RES_50_DIR = SCRIPT_DIR + '/' + RES_50
RES_25_DIR = SCRIPT_DIR + '/' + RES_25


def renew_dir(dir):
    if os.path.exists(dir):
        shutil.rmtree(dir)
    shutil.copytree(RES_100_DIR, dir)


def get_png_file_list(dir):
    file_list = []
    import os
    for root, dirs, files in os.walk(dir):
        for file in files:
            if file.endswith(".png"):
                file_list += [os.path.join(root, file)]
    return file_list


def scale_file(file, factor):
    image = Image.open(file)
    new_size = (image.size[0] / factor, image.size[1] / factor)
    image.resize(new_size, Image.NEAREST).save(file)


def scale(dir, factor):
    renew_dir(dir)
    file_list = get_png_file_list(dir)
    for file in file_list:
        scale_file(file, factor)


def resize_all():
    scale(RES_50_DIR, 2)
    scale(RES_25_DIR, 4)


if __name__ == "__main__":
    try:
        resize_all()
    except RuntimeError, Argument:
        print "ERROR " + str(Argument)
        sys.exit(1)

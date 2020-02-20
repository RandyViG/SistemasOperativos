#!/usr/bin/env python3 
import os
import subprocess as sub

who = sub.run('whoami',stdout=sub.PIPE)
who = who.stdout.decode('utf-8')
absolutePath = '/home/' + who[:-1]
backup = 'Backup'
mp4Path = backup + '/Mp4'
pdfPath = backup + '/Pdf'
jpgPath = backup + '/Jpg'

findMp4 = sub.run(['find',absolutePath,'-name','*.mp4'],stdout=sub.PIPE)
mp4 = findMp4.stdout.decode('utf-8').split('\n')

findPdf = sub.run(['find',absolutePath,'-name','*.pdf'],stdout=sub.PIPE)
pdf = findPdf.stdout.decode('utf-8').split('\n')

findJpg = sub.run(['find',absolutePath,'-name','*.jpg'],stdout=sub.PIPE)
jpg = findJpg.stdout.decode('utf-8').split('\n')

os.mkdir(backup)
os.mkdir(mp4Path)
os.mkdir(pdfPath)
os.mkdir(jpgPath)

for path in mp4:
    sub.run(['cp',path,mp4Path],stderr=sub.PIPE)

for path in pdf:
    sub.run(['cp',path,pdfPath],stderr=sub.PIPE)

for path in jpg:
    sub.run(['cp',path,jpgPath],stderr=sub.PIPE)

sub.run(['tar','-cvzf','backup.tar.gz',backup])

#os.removedirs(backup)
#os.remove(mp4Path)
#os.remove(pdfPath)
#os.remove(jpgPath)

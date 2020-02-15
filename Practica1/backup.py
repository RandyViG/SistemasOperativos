import os
import subprocess as sub

who = sub.run('whoami',stdout=sub.PIPE)
who = who.stdout.decode('utf-8')
absolutePath = '/home/' + who[:-1]
backup = 'Backup'
txtPath = backup + '/Txt'
pdfPath = backup + '/Pdf'
jpgPath = backup + '/Jpg'

findTxt = sub.run(['find',absolutePath,'-name','*.txt'],stdout=sub.PIPE)
txt = findTxt.stdout.decode('utf-8').split('\n')

findPdf = sub.run(['find',absolutePath,'-name','*.pdf'],stdout=sub.PIPE)
pdf = findPdf.stdout.decode('utf-8').split('\n')

findJpg = sub.run(['find',absolutePath,'-name','*.jpg'],stdout=sub.PIPE)
jpg = findJpg.stdout.decode('utf-8').split('\n')

os.mkdir(backup)
os.mkdir(txtPath)
os.mkdir(pdfPath)
os.mkdir(jpgPath)

for path in txt:
    sub.run(['cp',path,txtPath],stderr=sub.PIPE)

for path in pdf:
    sub.run(['cp',path,pdfPath],stderr=sub.PIPE)

for path in jpg:
    sub.run(['cp',path,jpgPath],stderr=sub.PIPE)

sub.run(['tar','-cvzf','backup.tar.gz',backup])


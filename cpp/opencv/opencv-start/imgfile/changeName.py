# encoding:utf-8
import os,sys




if __name__ == "__main__":
    #dir = r'F:\new 文件\stanford\algotithm-part1\videos'
    #dir = r'/home/fuxiang/code-fuxiang90/cpp/opencv/opencv-start/imgfile/4'
    #dir = r'.\ml\video'
    #dir = 'F:\\kankan'
    #print len(sys.argv) 
    if len(sys.argv) != 3:
        print "please use python changeName.py dirname classid "
        pass
    dir = sys.argv[1]
    classid = int(sys.argv[2])
    filenames=os.listdir(dir)

    pos = 0
    for i in xrange(len(filenames)):
        str1 = filenames[i]
        s = str(classid)+"-"
        if str1.find('jpg') != -1:
            str2 = s + str(pos)+'.jpg'
            pos = pos + 1
            os.rename(dir+os.sep+filenames[i],dir+os.sep+str2)

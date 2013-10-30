


from common.add import add

print add(1,2)

def test(s):

    if not (s.startswith('01') == True or s.startswith('02') == True ) :
        print 'out'
    else :
        print 'in'


l = ['01' , '02','03','04']
for s in l :
    test(s)

import multiprocessing
import time

def func(msg):
    d = {}
    for i in range(1000):
        d[i] = i
    return d
if __name__ == "__main__":
    pool = multiprocessing.Pool(processes=4)
    result = []
    for i in xrange(10):
        msg = "hello %d" %(i)
        d = (pool.apply_async(func, (msg, )))
        print type(d.get() )
        result.append(pool.apply_async(func, (msg, )))
    pool.close()
    pool.join()
    # for res in result:
    #     print res.get()
    print "Sub-process(es) done."

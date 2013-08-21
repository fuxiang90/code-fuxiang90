import multiprocessing
import Queue



class MainProcess(multiprocessing.Process):
    
    def __init__(self):
        multiprocessing.Process.__init__(self)
        self._queue = queue
        self._mysql_db = db_handle

    def run(self):
        while True :
            seed_url = None
            try:
                seed_url = self._queue.get(False)
            except Queue.Empty:
                break
            
            fo


def mult_crawl_process(processes):
    

    queue = multiprocessing.Queue() 


    for i in range(100) :
        queue.put(i)

    crawl_processes = []
    for _ in range(processes):
        process = MainProcess()
        crawl_processes.append(process)

    for crawl in crawl_processes :
        crawl.start()

    for crawl in crawl_processes:
        crawl.join()
if __name__ == "__main__":
        
    #crawl_main()
    
    mult_crawl_process(2)
    print "done it"

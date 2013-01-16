#include"Pipes.hh"
#include"TemplateFactory.hh"
#include"StringUtils.hh"

class DataCountMap:public HadoopPipes::Mapper
{
public:
    DataCountMap(HadoopPipes::TaskContext&context) {}
    void map(HadoopPipes::MapContext&context)
    {
        std::vector<std::string>words=HadoopUtils::splitString(context.getInputValue()," ");    // 这里是分割字符串，如前文所述，每一行数据中的各项是以空格来分割的。分割的结果保存到了一个std::vector中
        if("kkk"==words[1])
        {
            context.emit("kkk","1");
        }
        else if("nnn"==words[1])
        {
            context.emit("nnn","1");
        }
    }
};

class DataCountReduce:public HadoopPipes::Reducer
{
public:
    DataCountReduce(HadoopPipes::TaskContext&context) {}
    void reduce(HadoopPipes::ReduceContext&context)
    {
        int sum=0;
        while(context.nextValue())
        {
            sum++;
        }
        context.emit(context.getInputKey(),HadoopUtils::toString(sum));
    }
};

int main(int argc,char*argv[])
{
    return HadoopPipes::runTask(HadoopPipes::TemplateFactory<DataCountMap, DataCountReduce>());
}

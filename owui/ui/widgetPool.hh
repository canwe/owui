#ifndef _OBJECTS_POOL_HH_
#define _OBJECTS_POOL_HH_

#include <olibs/tools/objectPool.hh>
#include <olibs/base/object.hh>
#include <olibs/base/onlyOne.hh>
#include <olibs/thr/task.hh>
#include <olibs/thr/thread.hh>
#include <olibs/thr/mutex.hh>

#include <set>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>

// \todo: тут нужен пропуск в две строки
namespace Owui {
namespace Ui {

// \todo Никогда не делать константы в глобальными в H файлах. Никогда не делать их в виде define (за исключением микроконтроллеров)  
#define CLEANER_PERIOD        (1000)
#define CLEANER_FRIEQUNCY     (10)
   

// \todo Что тут связаного с owui? А если ничего, то почему это не в olibs/tools?
class PoolCleaner : public Olibs::OnlyOne<PoolCleaner>, Olibs::Thr::Task
{
public:
   PoolCleaner();
   void registrate(Olibs::Tools::ObjectCashe* cashe);
   
protected:
  virtual void taskFunc();
  
private:
   Olibs::Thr::Thread m_thread;
   unsigned m_count;
   Olibs::Thr::Mutex m_lock;
   
   typedef std::vector<Olibs::Tools::ObjectCashe*> PoolsContainer;
   PoolsContainer m_pools;   
};
// \todo: Тут ровно две строки надо пропускать      
   
class WidgetPool
{
public:
   WidgetPool();
   ~WidgetPool();

   Olibs::Object* alloc(const Olibs::String& objectName);
   void free(Olibs::Object* object);

// \todo Это делается через Olibs/base/factory   
   void addCreator(const Olibs::String& objectName, Olibs::Tools::ObjectFactoryCreator::BuildFunc buildFunc);
      
private:
  // \todo Зачем это когда уже есть map?
   typedef std::vector<Olibs::Tools::ObjectCashe*> PoolsContainer;
   PoolsContainer m_pools;
   
   typedef std::map<Olibs::Object*, Olibs::Tools::ObjectCashe*> UsedObjectAdressContainer;
   UsedObjectAdressContainer m_usedObjectAdress;
};
// \todo и тут две строки   

}}
// \todo Тут одна
#endif
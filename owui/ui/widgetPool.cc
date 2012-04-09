#if 0

#include <owui/ui/widgetPool.hh>
#include <olibs/base/assert.hh>
#include <olibs/lock/slock.hh>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <olibs/time/ut.hh>


namespace Owui {
namespace Ui {


PoolCleaner::PoolCleaner() :
   m_thread(*this), 
   m_count(0)
{
   m_thread.start();
}
   
void PoolCleaner::registrate(Olibs::Tools::ObjectCashe* cashe)
{
   Olibs::Lock::Slock locker(m_lock);
   
   m_pools.push_back(cashe);
}
   
void PoolCleaner::taskFunc()
{
   Olibs::Lock::Slock locker(m_lock);
   
   ++m_count;
   bool needClean = false;
   if(m_count == CLEANER_FRIEQUNCY)
      needClean = true;
   
   
   for(PoolsContainer::iterator pos = m_pools.begin(); pos != m_pools.end(); ++pos)
   {
      Olibs::Lock::Slock locker(*(*pos));
      (*pos)->countAverage();
      
      if(needClean)
      {
         unsigned cashedObjectsAmount = static_cast<unsigned>((*pos)->getAverageObjectAmount() * (1 + CASHED_OBJECTS_STOCK_PERSENT / 100));
         unsigned deleteObjectAmount = cashedObjectsAmount - (*pos)->getObjectsAmount();
         
         for(unsigned index = 0; index < deleteObjectAmount; ++index)
         {
            if((*pos)->getUnusedObjectmount() == 0)
               break;
            (*pos)->freeUnusedObject();
         }         
      }
   }
   
   
   Olibs::Time::sleep(CLEANER_PERIOD);
}


   
   
   
WidgetPool::~WidgetPool()
{
   for(PoolsContainer::iterator pos = m_pools.begin(); pos != m_pools.end(); ++pos)
   {
      delete *pos;
   }
   m_pools.clear();
}


struct FindStructByNamePredicate : public std::binary_function<Olibs::Tools::ObjectCashe*, Olibs::String, bool>
{
   bool operator() (const first_argument_type& cashe, const second_argument_type& name) const
   {
      if(cashe->className() == name)
         return true;
      else return false;
   }
};
Olibs::Object* WidgetPool::alloc(const Olibs::String& objectName)
{
   PoolsContainer::iterator pos = std::find_if(m_pools.begin(), m_pools.end(), std::bind2nd(FindStructByNamePredicate(), objectName));
   
   if(pos == m_pools.end()) 
   {
     // \todo Везде использовать olibs::String, olibs::Ostream и т.п.     
      std::string what = "no creator found: ";
      what += objectName;
// \todo Две вышеприведеные строки писать в одно выражение
      
      throw std::runtime_error(what);
   }
   // \todo Только одна пусая строка
   Olibs::Lock::Slock locker(*(*pos));
   
   Olibs::Object* object = (*pos)->alloc();
   m_usedObjectAdress.insert(std::make_pair(object, (*pos)));

   return object;
}



void WidgetPool::free(Olibs::Object* object)
{
   UsedObjectAdressContainer::iterator pos = m_usedObjectAdress.find(object);
   
   if(pos == m_usedObjectAdress.end())
   {
      throw std::runtime_error("no object found");
   }
   
   Olibs::Tools::ObjectCashe* cashe = pos->second;
   Olibs::Lock::Slock locker(*cashe);
   
   cashe->free(object);
}

void WidgetPool::addCreator(const Olibs::String& objectName, Olibs::Tools::ObjectFactoryCreator::BuildFunc buildFunc)
{
   PoolsContainer::iterator pos = std::find_if(m_pools.begin(), m_pools.end(), std::bind2nd(FindStructByNamePredicate(), objectName));
   
   if(pos != m_pools.end()) 
   {
      std::string what = "already exists: ";
      what += objectName;      
      throw std::runtime_error(what);
   }

   Olibs::Tools::ObjectFactoryCreator* creator = new Olibs::Tools::ObjectFactoryCreator(objectName, buildFunc);
   Olibs::Tools::ObjectCashe* cashe = new Olibs::Tools::ObjectCashe(*creator);
   
   m_pools.push_back(cashe);
   
   PoolCleaner::instance()->registrate(cashe);
}



   
}}

#endif

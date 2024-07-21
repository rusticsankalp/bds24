#pragma once
#include <cstdint>
#include <chrono>
#include <stdexcept>
#include <mutex>

namespace vera::uid
{
 class pseudo_lock
 {
   public:
    void lock(){}
    void unlock(){}
 };

 template<int64_t Twepoch, typename Lock = pseudo_lock>
 class snowflake
 {
    using lock_type = Lock;
    static constexpr int64_t TWEPOCH = Twepoch;
    
    //Sequence Bit info
    static constexpr int64_t SEQUENCE_BITS = 12L;
    static constexpr int64_t SEQUENCE_MASK = (1 <<SEQUENCE_BITS) -1;

    //Worker Id Bits
    static constexpr int64_t WORKER_ID_BITS = 5L;
    static constexpr int64_t MAX_WORKER_ID = (1 << WORKER_ID_BITS) -1;
    static constexpr int64_t WORKER_ID_SHIFT = SEQUENCE_BITS;

    //DataCenter Id Bits
    static constexpr int64_t DATACENTER_ID_BITS = 5L;
    static constexpr int64_t MAX_DATACENTER_ID = (1 << DATACENTER_ID_BITS) -1;
    static constexpr int64_t DATACENTER_ID_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS;

    //Timestamp Bits
    static constexpr int64_t TIMESTAMP_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS + DATACENTER_ID_BITS;
   
    
    using time_point = std::chrono::time_point<std::chrono::steady_clock>;
    time_point m_start_time = std::chrono::steady_clock::now();

    int64_t m_start_ms = std::chrono::duration_cast<std::chrono::milliseconds>
	    (std::chrono::system_clock::now().time_since_epoch()).count();

    int64_t m_last_timestamp {-1};
    int64_t m_worker_id {0};
    int64_t m_datacenter_id {0};
    int64_t m_sequence {0};
    lock_type m_lock;

   private:
    int64_t GetCurrentMS() const noexcept
    {
      auto diff = std::chrono::duration_cast<std::chrono::milliseconds>
	      (std::chrono::steady_clock::now() - m_start_time);

      return m_start_ms + diff.count();
    }

    int64_t WaitForNextMS(int64_t current) const noexcept
    {
      auto timestamp = GetCurrentMS();
      while(timestamp <= current);
      {
	timestamp = GetCurrentMS();
      }
      return timestamp;
    }
   public:

    //: TBD remove contructor
    //snowflake() = default;
    snowflake(const snowflake&) = delete;
    snowflake& operator=(const snowflake&) = delete;

   
   snowflake(int64_t wid, int64_t dcid)
   {
      if(wid > MAX_WORKER_ID || wid <0)
      {
	throw std::runtime_error("worker id can't be greater than 31 or less than 0");
      }

      if(dcid >MAX_DATACENTER_ID || dcid < 0)
      {
	throw std::runtime_error("data center id can't be greater than 31 or less than 0");
      }

      m_worker_id = wid;
      m_datacenter_id = dcid;
   }

   int64_t GetNextId()
   {
      std::lock_guard<lock_type> lock(m_lock);
      auto timestamp = GetCurrentMS();
      if(m_last_timestamp == timestamp)
      {
	m_sequence = (m_sequence+1) & SEQUENCE_MASK;
	if(m_sequence ==0)
	{
	  timestamp = WaitForNextMS(m_last_timestamp);
	}
      }
      else
      {
	m_sequence =0;
      }
      
      m_last_timestamp = timestamp;
      return timestamp;
   }
 };
}



#include <hc32_ll.h>
#include <symbol.h>

/**
 * @brief 将数据从flash拷贝到ram。
 * @param dest 拷贝数据到该地址。
 * @param src 从该地址拷贝数据。
 * @param len 拷贝字节数.
 */
static inline char* reset_copy_ram_init(char* dest, const char* src, size_t len)
{
        // 小数据量处理
        if (len < 4)
        {
                while (len--)
                        *dest++ = *src++;
                return dest;
        }

        // 对齐处理（尝试将目标地址对齐到4字节边界）
        // 检查地址是否对齐到4字节
        while (((uintptr_t)dest & 0x3) != 0 && len > 0)
        {
                *dest++ = *src++;
                len--;
        }

        // 32位宽数据拷贝（核心优化）
        uint32_t* d32 = (uint32_t*)dest;
        const uint32_t* s32 = (const uint32_t*)src;

        // 使用循环展开：一次处理16字节（4个32位字）
        // 这样可以减少循环次数和判断开销
        while (len >= 16)
        {
                d32[0] = s32[0];
                d32[1] = s32[1];
                d32[2] = s32[2];
                d32[3] = s32[3];
                d32 += 4;
                s32 += 4;
                len -= 16;
        }

        // 处理剩余的32位字
        while (len >= 4)
        {
                *d32++ = *s32++;
                len -= 4;
        }

        // 处理剩余的字节
        dest = (char*)d32;
        src = (const char*)s32;
        while (len--)
        {
                *dest++ = *src++;
        }

        return dest;
}

/**
 * @brief 将ram指定区域清零。
 * @param start 起始地址。
 * @param end   结束地址。
 */
static inline char* reset_clear_ram_uninit(char* start, char* end)
{
        // 将8位字符扩展为32位模式
        // 将c转换为无符号8位，然后填充到32位变量中
        uint8_t val8 = 0u;
        uint32_t val32 = (uint32_t)val8;
        val32 |= (val32 << 8);
        val32 |= (val32 << 16);
        uint32_t n = (uint32_t)end - (uint32_t)start;

        // 字节对齐前的填充（处理起始不齐的部分）
        while (((uintptr_t)start & 0x3) != 0 && n > 0)
        {
                *start++ = val8;
                n--;
        }

        // 32位宽批量填充（核心优化）
        uint32_t* p32 = (uint32_t*)start;

        // 循环展开：一次填充16字节
        while (n >= 16)
        {
                p32[0] = val32;
                p32[1] = val32;
                p32[2] = val32;
                p32[3] = val32;
                p32 += 4;
                n -= 16;
        }

        // 处理剩余的32位字
        while (n >= 4)
        {
                *p32++ = val32;
                n -= 4;
        }

        // 处理最后的剩余字节
        start = (char*)p32;
        while (n--)
        {
                *start++ = val8;
        }

        return start;
}

/**
 * @brief 复位处理函数，配置程序运行所需的环境，
 * 包括设置栈初始指针、开启mcu内核相关配置、初始化ram数据、
 * 根据条件跳转到指定程序开始执行。
 */
void Reset_Handler(void)
{
        // 设置初始栈指针
        __set_MSP((uint32_t)_msp_top);

        /* 加载 fast 的数据 */
        reset_copy_ram_init((char*)_fast_data_ram_start, _fast_data_flash_addr,
                            (size_t)_fast_data_ram_end -
                                    (size_t)_fast_data_ram_start);

        /* 加载 init 的数据 */
        reset_copy_ram_init((char*)_init_data_ram_start, _init_data_flash_addr,
                            (size_t)_init_data_ram_end -
                                    (size_t)_init_data_ram_start);

        /* 清空 uninit 的数据 */
        reset_clear_ram_uninit((char*)_uninit_data_ram_start,
                               (char*)_uninit_data_ram_end);

        /* 进入启动流程 */
        extern void startup(void);
        startup();
}
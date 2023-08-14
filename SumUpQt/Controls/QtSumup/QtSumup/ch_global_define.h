#pragma once
#include <QApplication>
#define SOURCE_DIR (QCoreApplication::applicationDirPath() + "/stylesheet/")
#define CONFIG_DIR (QCoreApplication::applicationDirPath() + "/configs/")
#define CH_NULLPTR_RETURN(ptr, ...) do{if (nullptr == ptr) return ##__VA_ARGS__;}while(0);
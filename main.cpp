
#include <stdio.h>

#ifndef __USE_GNU
#	define __USE_GNU
#endif

#include <dlfcn.h>
#include <typeinfo>
#include <QtCore/QMetaObject>

#define INVOKE_PARAMS QObject * obj, const char * member, Qt::ConnectionType type, QGenericReturnArgument ret, QGenericArgument val0, QGenericArgument val1, QGenericArgument val2, QGenericArgument val3, QGenericArgument val4, QGenericArgument val5, QGenericArgument val6, QGenericArgument val7, QGenericArgument val8, QGenericArgument val9

typedef bool (*InvokePtr)(INVOKE_PARAMS);

static InvokePtr real_invoke=NULL;


static void __sigtrace_init(void) {
    real_invoke = (InvokePtr) dlsym(RTLD_NEXT, "_ZN11QMetaObject12invokeMethodEP7QObjectPKcN2Qt14ConnectionTypeE22QGenericReturnArgument16QGenericArgumentS7_S7_S7_S7_S7_S7_S7_S7_S7_");
    if (real_invoke == NULL) {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
        return;
    }
}

void printInvokeDetails(INVOKE_PARAMS) {
	const char *className = typeid(obj).name();
	fprintf(stderr, "QMetaObject::invokeMethod(%s 0x%08llx, member='%s')\n", className, (long long) obj, member);
}

bool QMetaObject::invokeMethod(INVOKE_PARAMS) {
	if(real_invoke==NULL)
		__sigtrace_init();

	printInvokeDetails(obj, member, type, ret, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
	return real_invoke(obj, member, type, ret, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
}

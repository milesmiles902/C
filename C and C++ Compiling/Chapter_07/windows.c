#ifdef CUSTOMER_XYZ
#pragma comment(lib, "<customerXYZ-specific library>");
#else
#ifdef CUSTOMER_ABC
#pragma comment(lib, "<customerABC-specific library>");
#else
#ifdef CUSTOMER_MPQ
#pragma comment(lib, "<customerMPQ-specific library>");
#endif // CUSTOMER_MPQ
#endif // CUSTOMER_ABC
#endif // CUSTOMER_XYZ


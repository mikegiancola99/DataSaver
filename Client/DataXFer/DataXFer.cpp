// ************************************************************************
// Copyright 2012 Mike Giancola
// All rights reserved
// ************************************************************************
#include "DataXFer.h"
#include <msxml6.h>
#include <comutil.h>

bool DataXFer::SendPostback()
{
    wstring message;
	bool success = false;
	IXMLHttpRequest* pXMLHttpReq = 0;
	HRESULT hr = CoCreateInstance(CLSID_XMLHTTP, NULL, CLSCTX_INPROC_SERVER, IID_IXMLHTTPRequest, (void**)&pXMLHttpReq);
	if (hr == S_OK)
	{
		wstring svcURL = L"http://www.somewhere.com/data/Service.asmx";
		hr = pXMLHttpReq->open(_bstr_t(L"POST"), _bstr_t(svcURL.c_str()), _variant_t(VARIANT_FALSE), _variant_t(VT_NULL), _variant_t(VT_NULL));
		if (hr == S_OK)
		{
			pXMLHttpReq->setRequestHeader(L"Content-Type", L"text/xml; charset=utf-8");
			pXMLHttpReq->setRequestHeader(L"SOAPAction", L"http://www.somewhere.com/LogData");
			BSTR tmp = _bstr_t(message.c_str());
			VARIANT varTmp = _variant_t(message.c_str());
			hr  = pXMLHttpReq->send(varTmp);
			if (hr == S_OK)
			{
				IXMLDOMDocument* m_pXMLDoc;
				hr = pXMLHttpReq->get_responseXML((IDispatch **) &m_pXMLDoc);
				if (hr == S_OK)
					success = true;
			}
			pXMLHttpReq->abort();
		}
	}
	return success;
}

bool DataXFer::SendFile(const wstring& inFile)
{
    bool success = false;
    




    return success;
}
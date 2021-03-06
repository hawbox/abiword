

#ifndef __gr_AbiLasemMathManager_h__
#define __gr_AbiLasemMathManager_h__
#include "ut_string_class.h"
#include "gr_EmbedManager.h"
#include "gr_Graphics.h"
#include "ut_types.h"
#include "ut_math.h"
#include "ut_vector.h"


#include <goffice/goffice.h>
#include <cairo-svg.h>
#include <lsmdom.h>


#include "ie_imp_MathML.h"

class GR_Graphics;
class PD_Document;
class AD_Document;
class LasemMathView;
class GR_AbiMathItems;

struct write_state {
	size_t length;
	GsfOutput *output;
};


class GR_AbiMathItems
{
public:
	GR_AbiMathItems();
	virtual ~GR_AbiMathItems();
	UT_uint32 m_iAPI;
	bool m_bHasSnapshot;
};

class GR_LasemMathManager : public GR_EmbedManager
{
public:
	GR_LasemMathManager(GR_Graphics * pG);
	virtual ~GR_LasemMathManager();
	virtual GR_EmbedManager* create(GR_Graphics * pG) override;
	virtual const char* getObjectType(void) const override;
	virtual void initialize(void) override;
	virtual UT_sint32 makeEmbedView(AD_Document * pDoc, UT_uint32  api, const char * szDataID) override;
	virtual void setColor(UT_sint32 uid, const UT_RGBColor& c) override;
	virtual bool setFont(UT_sint32 uid, const GR_Font * pFont) override;
	virtual void setDisplayMode(UT_sint32 uid, AbiDisplayMode mode) override;
	virtual UT_sint32 getWidth(UT_sint32 uid) override;
	virtual UT_sint32 getAscent(UT_sint32 uid) override;
	virtual UT_sint32 getDescent(UT_sint32 uid) override;
	virtual void loadEmbedData(UT_sint32 uid) override;
	virtual void setDefaultFontSize(UT_sint32 uid, UT_sint32 iSize) override;
	virtual void render(UT_sint32 uid, UT_Rect & rec) override;
	virtual void releaseEmbedView(UT_sint32 uid) override;
	virtual void initializeEmbedView(UT_sint32 uid) override;
	virtual void makeSnapShot(UT_sint32 uid, UT_Rect & rec) override;
	virtual bool isDefault(void) override;
	virtual bool convert(UT_uint32 iConv, const UT_ConstByteBufPtr & From, const UT_ByteBufPtr & To) override;
	virtual void updateData(UT_sint32 uid, UT_sint32 api) override;
	virtual bool isEdittable(UT_sint32 uid) override;
	virtual void setRun(UT_sint32 uid, fp_Run * run) override;
	const IE_Imp_MathML_EntityTable & EntityTable() const { return m_EntityTable; }

    static LasemMathView * last_created_view;

private:
	UT_sint32                              _makeLasemMathView(void);
	void                                    _loadMathMl(UT_sint32 uid, UT_UTF8String & sGOChartBuf);
	UT_sint32                              _getNextUID(void);
	UT_sint32                              m_CurrentUID;
	UT_GenericVector<LasemMathView *>        m_vecLasemMathView;
	UT_GenericVector<GR_AbiMathItems *>    m_vecItems;
	PD_Document *                          m_pDoc;
	IE_Imp_MathML_EntityTable              m_EntityTable;
};

class LasemMathView
{
public:
	LasemMathView(GR_LasemMathManager  * pMathMan);
	virtual ~LasemMathView(void);
	void render(UT_Rect & rec);
	void setFont(const GR_Font * pFont); 
	void setColor(const UT_RGBColor& c);
	void setDisplayMode(AbiDisplayMode mode);
	void setItex(char * itex); 
	void loadBuffer(UT_UTF8String & sMathml);
	void SetRun(fp_Run *pRun) {m_pRun = pRun;}
	fp_Run *getRun() {return m_pRun;}
	void SetGuru(GtkWidget *guru) {m_Guru = guru;}
	UT_ConstByteBufPtr exportToSVG();
	UT_ConstByteBufPtr getSnapShot();
	UT_sint32 getWidth() {return width;}
	UT_sint32 getHeight() {return height;}
	UT_sint32 getAscent() {return ascent;}
	UT_sint32 getDescent(){return descent;}
private:
	GR_LasemMathManager  * m_pMathMan;

	char *itex;
	char *font;
	char *color;
	bool compact;
	
	LsmDomDocument *mathml;
	LsmDomNode *math_element;
	LsmDomNode *style_element;

	LsmDomView *view;
		
	UT_sint32 width, height, ascent, descent, m_y;
	fp_Run *m_pRun;

	GtkWidget *m_Guru;
};

#endif // __gr_AbiLasemMathManager_h__

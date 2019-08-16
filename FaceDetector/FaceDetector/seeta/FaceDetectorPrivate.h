#ifndef _FACE_DETECTOR_PRIVATE_H_
#define _FACE_DETECTOR_PRIVATE_H_


#include <cstdint>
#include <vector>

#include "CFaceInfo.h"
#include "CStruct.h"


/** @class FaceDetectorPrivate FaceDetectorPrivate.h
*  @brief The face detector.
*/
class FaceDetectorPrivate {
public:

    class CoreSize {
    public:
        CoreSize() : width( -1 ), height( -1 ) {}
        CoreSize( int width, int height ) : width( width ), height( height ) {}

        int width;
        int height;
    };


    /**
     * \brief �������������
     * \param [in] model_path �����·��
     * \note Ĭ�ϻ��� AUTO ģʽʹ�ü����豸
     */
    explicit FaceDetectorPrivate( const char *model_path );

    /**
     * \brief �������������
     * \param [in] model_path �����·��
     * \param [in] device ʹ�õļ����豸
     */
    explicit FaceDetectorPrivate( const char *model_path, SeetaDevice device, int gpuid );

    /**
     * \brief �������������
     * \param [in] model_path �����·��
     * \note Ĭ�ϻ��� AUTO ģʽʹ�ü����豸
     */
    explicit FaceDetectorPrivate( const char *model_path, const CoreSize &core_size );

    /**
     * \brief �������������
     * \param [in] model_path �����·��
     * \param [in] device ʹ�õļ����豸
     */
    explicit FaceDetectorPrivate( const char *model_path, const CoreSize &core_size, SeetaDevice device, int gpuid );

    ~FaceDetectorPrivate();

    /**
     * \brief �������
     * \param [in] img ����ͼ����Ҫ RGB ��ɫͨ��
     * \return ��⵽��������VIPLFaceInfo������
     * \note �˺�����֧�ֶ��̵߳��ã��ڶ��̻߳�������Ҫ������Ӧ�� FaceDetectorPrivate �Ķ���ֱ���ü�⺯��
     * \seet VIPLFaceInfo, VIPLImageData
     */
    SeetaFaceInfoArray Detect( const SeetaImageData &img );

    /**
     * \brief ������С����
     * \param [in] size ��С�ɼ���������С��Ϊ������͸߳˻��Ķ��θ�ֵ
     * \note ��������Ϊ 20��С�� 20 ��ֵ�ᱻ����
     */
    void SetMinFaceSize( int32_t size );

    /**
     * \brief ����ͼ������������ű���
     * \param [in] factor ���ű���
     * \note ��ֵ��СΪ 1.414��С�� 1.414 ��ֵ�ᱻ����
     */
    void SetImagePyramidScaleFactor( float factor );

    /**
     * \brief ���ü�����·�����������ֵ
     * \param [in] thresh1 ��һ����ֵ
     * \param [in] thresh2 �ڶ�����ֵ
     * \param [in] thresh3 ��������ֵ
     * \note Ĭ���Ƽ�Ϊ��0.62, 0.47, 0.985
     */
    void SetScoreThresh( float thresh1, float thresh2, float thresh3 );

    /**
    * \brief ��ȡ��С����
    * \return size ��С�ɼ���������С��Ϊ������͸߳˻��Ķ��θ�ֵ
    */
    int32_t GetMinFaceSize() const;

    /**
    * \brief ��ȡͼ������������ű���
    * \return factor ���ű���
    */
    float GetImagePyramidScaleFactor() const;

    /**
     * \brief ��ȡ������·�����������ֵ
     * \param [out] thresh1 ��һ����ֵ
     * \param [out] thresh2 �ڶ�����ֵ
     * \param [out] thresh3 ��������ֵ
     * \note ��������Ϊ nullptr����ʾ��ȡ��ֵ
     */
    void GetScoreThresh( float *thresh1, float *thresh2, float *thresh3 ) const;

    float GetScoreThresh1() const;
    float GetScoreThresh2() const;
    float GetScoreThresh3() const;

    void SetScoreThresh1( float thresh1 );
    void SetScoreThresh2( float thresh2 );
    void SetScoreThresh3( float thresh3 );
    /**
     * \brief �Ƿ����ȶ�ģʽ������������
     * \param stable �Ƿ��ȶ�
     * \note Ĭ���ǲ����ȶ�ģ�͹�����
     * \note ֻ������Ƶ����������ʱ����ʹ�ô˷���
     */
    void SetVideoStable( bool stable = true );

    /**
     * \brief ��ȡ��ǰ�Ƿ����ȶ�����ģʽ
     * \return �Ƿ��ȶ�
     */
    bool GetVideoStable() const;

    CoreSize GetCoreSize() const;

private:
    FaceDetectorPrivate( const FaceDetectorPrivate &other ) = delete;
    const FaceDetectorPrivate &operator=( const FaceDetectorPrivate &other ) = delete;

private:
    void *impl_;
    std::vector<SeetaFaceInfo> m_pre_faces;
    static int m_threads;
};

#endif  // VIPL_FACE_DETECTOR_H_

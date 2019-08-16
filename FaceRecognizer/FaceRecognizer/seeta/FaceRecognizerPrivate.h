#ifndef _SEETA_FACE_RECOGNIZER_H
#define _SEETA_FACE_RECOGNIZER_H



#include "Struct.h"
#include <vector>



class FaceRecognizerModel {
public:
    friend class FaceRecognizerPrivate;

    FaceRecognizerModel( const char *model_path, int device );
    ~FaceRecognizerModel();
private:
    void *m_impl;
};

class FaceRecognizerPrivate {
public:
    class Param;
    const Param *GetParam() const;

    explicit FaceRecognizerPrivate( const Param *param );

    explicit  FaceRecognizerPrivate( const FaceRecognizerModel &model );



    /**
    * \brief ����ʶ����
    * \param [in] modelPath ʶ����ģ��·��
    * \note ʶ����ģ��һ��Ϊ FaceRecognizerPrivate5.0.XXX.dat
    * \note ���ֻ��ʹ�������ü��Ĳ��֣�����Ҫ����ģ��
    * \note Ĭ�ϻ��� AUTO ģʽʹ�ü����豸
    */
    explicit FaceRecognizerPrivate( const char *modelPath = NULL );

    /**
    * \brief ����ʶ����
    * \param [in] modelPath ʶ����ģ��·��
    * \param [in] device ʹ�õļ����豸
    * \note ʶ����ģ��һ��Ϊ FaceRecognizerPrivate5.0.XXX.dat
    * \note ���ֻ��ʹ�������ü��Ĳ��֣�����Ҫ����ģ��
    */
    explicit FaceRecognizerPrivate( const char *modelPath, SeetaDevice device, int gupid = 0 );

    /**
    * \brief ����ʶ����
    * \param [in] modelBuffer ʶ��ģ�͵��ڴ����
    * \param [in] bufferLength ʶ��ģ�͵��ڴ泤��
    * \note ʶ����ģ��һ��Ϊ FaceRecognizerPrivate5.0.XXX.dat
    * \note ���ֻ��ʹ�������ü��Ĳ��֣�����Ҫ����ģ��
    */
    explicit FaceRecognizerPrivate( const char *modelBuffer, size_t bufferLength, SeetaDevice device = SEETA_DEVICE_AUTO, int gpuid = 0 );

    ~FaceRecognizerPrivate();

    /**
    * \brief Ϊʶ��������ģ�ͣ���ж��ԭ����ģ��
    * \param [in] modelPath ʶ��ģ��·��
    * \return ���سɹ��󷵻���
    * \note �˺�����Ϊ���ڹ����ʱ��û�м���ģ�͵�����µ���
    * \note Ĭ�ϻ��� AUTO ģʽʹ�ü����豸
    */
    bool LoadModel( const char *modelPath );

    /**
    * \brief Ϊʶ��������ģ�ͣ���ж��ԭ����ģ��
    * \param [in] modelPath ʶ��ģ��·��
    * \param [in] device ʹ�õļ����豸
    * \return ���سɹ��󷵻���
    * \note �˺�����Ϊ���ڹ����ʱ��û�м���ģ�͵�����µ���
    */
    bool LoadModel( const char *modelPath, SeetaDevice device, int gpuid = 0 );

    /**
    * \brief Ϊʶ��������ģ�ͣ���ж��ԭ����ģ��
    * \param [in] modelBuffer ʶ��ģ�͵��ڴ����
    * \param [in] bufferLength ʶ��ģ�͵��ڴ泤��
    * \param [in] device ʹ�õļ����豸
    * \return ���سɹ��󷵻���
    * \note �˺�����Ϊ���ڹ����ʱ��û�м���ģ�͵�����µ���
    */
    bool LoadModel( const char *modelBuffer, size_t bufferLength, SeetaDevice device = SEETA_DEVICE_AUTO, int gpuid = 0 );

    /**
     * \brief ��ȡʶ������ȡ����ά��
     * \return ����ά��
     */
    uint32_t GetFeatureSize();

    /**
     * \brief ��ȡ����ʶ����ü�������ͼƬ���
     * \return ����ͼƬ���
     */
    uint32_t GetCropWidth();

    /**
    * \brief ��ȡ����ʶ����ü�������ͼƬ�߶�
    * \return ����ͼƬ�߶�
    */
    uint32_t GetCropHeight();

    /**
    * \brief ��ȡ����ʶ����ü�������ͼƬͨ����
    * \return ����ͼƬͨ����
    */
    uint32_t GetCropChannels();

    /**
     * \brief �ü�����
     * \param [in] srcImg ԭʼͼ�񣬲�ɫ
     * \param [in] llpoint ԭʼͼ�������������㣬5��
     * \param [out] dstImg Ŀ��ͼ�񣬸��ݲü���ϢԤ��������ڴ�
     * \param [in] posNum ������̬�������������˰汾������
     * \return ֻ�вü��ɹ���ŷ�����
     */
    bool CropFace( const SeetaImageData &srcImg,
                   const SeetaPointF *llpoint,
                   SeetaImageData &dstImg,
                   uint8_t posNum = 1 );

    /**
     * \brief �ڲü��õ���������ȡ����
     * \param [in] cropImg �ü��õ���������ɫ����ʹ�� CropFace ���߶�Ӧ����
     * \param [out] feats ����ȡ������ſռ�
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeature( const SeetaImageData &cropImg,
                         float *feats );

    /**
     * \brief �ڲü��õ���������ȡ��������һ���ģ�
     * \param [in] cropImg �ü��õ���������ɫ����ʹ�� CropFace ���߶�Ӧ����
     * \param [out] feats ����ȡ������ſռ�
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeatureNormalized( const SeetaImageData &cropImg,
                                   float *feats );

    /**
     * \brief ��ԭʼͼ���ϣ����ݶ�λ����ȡ����
     * \param [in] srcImg ԭʼͼ�񣬲�ɫ
     * \param [in] llpoint ԭʼͼ�������������㣬5��
     * \param [out] feats ����ȡ������ſռ�
     * \param [in] posNum ������̬�������������˰汾������
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeatureWithCrop( const SeetaImageData &srcImg,
                                 const SeetaPointF *llpoint,
                                 float *feats,
                                 uint8_t posNum = 1 );

    /**
     * \brief ��ԭʼͼ���ϣ����ݶ�λ����ȡ��������һ���ģ�
     * \param [in] srcImg ԭʼͼ�񣬲�ɫ
     * \param [in] llpoint ԭʼͼ�������������㣬5��
     * \param [out] feats ����ȡ������ſռ�
     * \param [in] posNum ������̬�������������˰汾������
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeatureWithCropNormalized( const SeetaImageData &srcImg,
                                           const SeetaPointF *llpoint,
                                           float *feats,
                                           uint8_t posNum = 1 );

    /**
     * \brief �������� fc1 �� fc2 �����ƶ�
     * \param [in] fc1 ��������1
     * \param [in] fc2 ��������2
     * \param [in] dim ����ά��
     * \return ���ƶ�
     * \note Ĭ������ά��Ӧ���� GetFeatureSize() �ķ���ֵ��������ǣ�����Ҫ�����Ӧ����������
     */
    float CalcSimilarity( const float *fc1,
                          const float *fc2,
                          long dim = -1 );

    /**
     * \brief �������� fc1 �� fc2 �����ƶ�
     * \param [in] fc1 ��������1����һ���ģ�
     * \param [in] fc2 ��������2����һ���ģ�
     * \param [in] dim ����ά��
     * \return ���ƶ�
     * \note Ĭ������ά��Ӧ���� GetFeatureSize() �ķ���ֵ��������ǣ�����Ҫ�����Ӧ����������
     * \note �˼������ƶȺ������������һ���������������ɺ�׺ Normalized �ĺ�����ȡ������
     */
    float CalcSimilarityNormalized( const float *fc1,
                                    const float *c2,
                                    long dim = -1 );

    /**
     * \brief ������󵥴�����������
     * \param max_batch ���������
     * \return ����֮ǰ������
     * \note ע��˺�������֮�����е�ʶ�������󶼻�ĳ�������ã���ʱ��֧�ֶ�ÿ����������
     */
    static int SetMaxBatchGlobal( int max_batch );

    /**
     * \brief ��ȡ��ǰʶ���������������������
     * \return ���������
     */
    int GetMaxBatch();

    /**
    * \brief ������ʶ���������߳���
    * \param core_number �����߳���
    * \return ����֮ǰ������
    * \note ע��˺�������֮�����е�ʶ�������󶼻�ĳ�������ã���ʱ��֧�ֶ�ÿ����������
    */
    static int SetCoreNumberGlobal( int core_number );

    /**
    * \brief ��ȡ��ǰʶ���������߳���
    * \return �����߳���
    */
    int GetCoreNumber();

    /**
     * \brief ������ȡ����
     * \param faces �ü��õ�ÿһ������
     * \param [out] feats �����ȡ�����Ŀռ䣬��СΪ faces.size() * GetFeatureSize()���� i * GetFeatureSize() �±꿪ʼ�� GetFeatureSize() �������ǵ�i����������
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeature( const std::vector<SeetaImageData> &faces, float *feats, bool normalization = false );

    /**
     * \brief ������ȡ��������һ���ģ�
     * \param faces �ü��õ�ÿһ������
     * \param [out] feats �����ȡ�����Ŀռ䣬��СΪ faces.size() * GetFeatureSize()���� i * GetFeatureSize() �±꿪ʼ�� GetFeatureSize() �������ǵ�i����������
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeatureNormalized( const std::vector<SeetaImageData> &faces, float *feats );

    /**
     * \brief ������ȡ����
     * \param images ԭʼͼ��
     * \param points ԭʼͼ���ϵ�ÿһ����������СΪ images.size() * 5���� i * 5 �±꿪ʼ�� 5 ���ǵ� i ��ͼƬ�ϵ�������
     * \param [out] feats �����ȡ�����Ŀռ䣬��СΪ images.size() * GetFeatureSize()���� i * GetFeatureSize() �±꿪ʼ�� GetFeatureSize() �������ǵ�i����������
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeatureWithCrop( const std::vector<SeetaImageData> &images, const std::vector<SeetaPointF> &points, float *feats, bool normalization = false );

    /**
     * \brief ������ȡ��������һ���ģ�
     * \param images ԭʼͼ��
     * \param points ԭʼͼ���ϵ�ÿһ����������СΪ images.size() * 5���� i * 5 �±꿪ʼ�� 5 ���ǵ� i ��ͼƬ�ϵ�������
     * \param [out] feats �����ȡ�����Ŀռ䣬��СΪ images.size() * GetFeatureSize()���� i * GetFeatureSize() �±꿪ʼ�� GetFeatureSize() �������ǵ�i����������
     * \return ֻ����ȡ�ɹ���ŷ�����
     */
    bool ExtractFeatureWithCropNormalized( const std::vector<SeetaImageData> &images, const std::vector<SeetaPointF> &points, float *feats );

private:
    FaceRecognizerPrivate( const FaceRecognizerPrivate &other ) = delete;
    const FaceRecognizerPrivate &operator=( const FaceRecognizerPrivate &other ) = delete;

private:
    class Recognizer;
    friend class FaceRecognizerModel;
    Recognizer *recognizer;
};
#endif // _SEETA_FACE_RECOGNIZER_H

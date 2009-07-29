/*
 * GStreamer
 * Copyright 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright 2005 S�bastien Moutte <sebastien@moutte.net>
 * Copyright 2006 Joni Valtanen <joni.valtanen@movial.fi>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */  
    
/*
  TODO: add device selection and check rate etc.
*/ 
    
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif /* 
    
#include <gst/gst.h>
#include <gst/audio/gstbaseaudiosrc.h>
    
#include "gstdirectsoundsrc.h"
    
#include <windows.h>
#include <dsound.h>
    

#define GST_CAT_DEFAULT directsoundsrc_debug

    
    
    

/* defaults here */ 
#define DEFAULT_DEVICE 0
    
/* properties */ 
    enum
{ 
};

    


    

    



    




    




    
    
        "endianness = (int) { LITTLE_ENDIAN, BIG_ENDIAN }, " 
        "signed = (boolean) { TRUE, FALSE }, " 
        "depth = (int) 16, " 
        "channels = (int) [ 1, 2 ]; " 
        "signed = (boolean) { TRUE, FALSE }, " 
        "depth = (int) 8, " 
        "channels = (int) [ 1, 2 ]"));

gst_directsound_src_do_init (GType type) 
{
  
      

    GstAudioSrc, 

gst_directsound_src_dispose (GObject * object) 
{
  


gst_directsound_src_finalise (GObject * object) 
{
  
  


gst_directsound_src_base_init (gpointer g_class) 
{
  
  
  
  
      


/* initialize the plugin's class */ 
static void 
gst_directsound_src_class_init (GstDirectSoundSrcClass * klass) 
{
  
  
  
  
  
  
  
  
  
  
  
  
  
  
      GST_DEBUG_FUNCPTR (gst_directsound_src_get_property);
  
      GST_DEBUG_FUNCPTR (gst_directsound_src_set_property);
  
      GST_DEBUG_FUNCPTR (gst_directsound_src_getcaps);
  
  
  
  
  
      GST_DEBUG_FUNCPTR (gst_directsound_src_unprepare);
  
  


gst_directsound_src_getcaps (GstBaseSrc * bsrc) 
{
  
  
  
  
  
          (bsrc)));
  



gst_directsound_src_set_property (GObject * object, guint prop_id,
    
{
  
      //  GstDirectSoundSrc *src = GST_DIRECTSOUND_SRC (object);
      GST_DEBUG ("set property\n");
  
    
      
#if 0
          /* FIXME */ 
    case PROP_DEVICE:
      
      
      
#endif /* 
    default:
      
      
    



gst_directsound_src_get_property (GObject * object, guint prop_id,
    
{
  
#if 0
      GstDirectSoundSrc * src = GST_DIRECTSOUND_SRC (object);
  
#endif /* 
      
  
      
#if 0
          /* FIXME */ 
    case PROP_DEVICE:
      
      
      
#endif /* 
    default:
      
      
  



/* initialize the new element
 * instantiate pads and add them to element
 * set functions
 * initialize structure
 */ 
static void 
gst_directsound_src_init (GstDirectSoundSrc * src,
    
{
  
  


gst_directsound_src_open (GstAudioSrc * asrc) 
{
  
  
  
  
  
      /* Open dsound.dll */ 
      dsoundsrc->DSoundDLL = LoadLibrary ("dsound.dll");
  
    
  
  
      /* Building the DLL Calls */ 
      pDSoundCaptureCreate = 
      (void *) GetProcAddress (dsoundsrc->DSoundDLL,
      
  
      /* If everything is not ok */ 
      if (!pDSoundCaptureCreate) {
    
  
  
      /* FIXME: add here device selection */ 
      /* Create capture object */ 
      hRes = pDSoundCaptureCreate (NULL, &dsoundsrc->pDSC, NULL);
  
    
  
  

    
    
        ("Unable to get capturecreate function"), (NULL));
    
  

    
    
        ("Unable to create capture object"), (NULL));
    
  

    
        ("Unable to open dsound.dll"), (NULL));
    
  



gst_directsound_src_close (GstAudioSrc * asrc) 
{
  
  
  
  
  
      /* Release capture handler  */ 
      hRes = IDirectSoundCapture_Release (dsoundsrc->pDSC);
  
      /* Close library */ 
      FreeLibrary (dsoundsrc->DSoundDLL);
  



gst_directsound_src_prepare (GstAudioSrc * asrc, GstRingBufferSpec * spec) 
{
  
  
  
  
  
  
  
  
      /* Define buffer */ 
      memset (&wfx, 0, sizeof (WAVEFORMATEX));
  
  
  
  
  
  
  
  
      /* 1 or 2 Channels etc...
         FIXME: Never really tested. Is this ok?
       */ 
      if (spec->width == 16 && spec->channels == 1) {
    
  
    
  
    
  
    
  
  
      /* Set the buffer size to two seconds. 
         This should never reached. 
       */ 
      dsoundsrc->buffer_size = wfx.nAvgBytesPerSec * 2;
  
      //notifysize * 16; //spec->width; /*original 16*/
      GST_DEBUG ("Buffer size: %d", dsoundsrc->buffer_size);
  
      /* Init secondary buffer desciption */ 
      memset (&descSecondary, 0, sizeof (DSCBUFFERDESC));
  
  
  
  
      /* This is not primary buffer so have to set size  */ 
      descSecondary.dwBufferBytes = dsoundsrc->buffer_size;
  
  
      /* Create buffer */ 
      hRes =
      IDirectSoundCapture_CreateCaptureBuffer (dsoundsrc->pDSC, 
      
  
    
  
  
  
  
  
  
      spec->buffer_time);
  
      /* Buffer-time should be allways more than 2*latency */ 
      if (spec->buffer_time < spec->latency_time * 2) {
    
    
  
  
      /* Save the times */ 
      dsoundsrc->buffer_time = spec->buffer_time;
  
  
      (gint) wfx.nAvgBytesPerSec * 
  
      (guint) (((double) spec->buffer_time / 1000000.0) * 
  
      /* just in case */ 
      if (spec->segsize < 1)
    
  
  
      
      
  
  
  
  
  
    
  
      /* Not readed anything yet */ 
      dsoundsrc->current_circular_offset = 0;
  
GstRingBufferSpec->bytes_per_sample: %d\n\
WAVEFORMATEX.nSamplesPerSec: %ld, WAVEFORMATEX.wBitsPerSample: %d, \
WAVEFORMATEX.nBlockAlign: %d, WAVEFORMATEX.nAvgBytesPerSec: %ld\n", 
  

    
        ("Unable to get format %d", spec->format), (NULL));
    
  

    
        ("Unable to create capturebuffer"), (NULL));
    
  

    
        ("Unexpected width %d", spec->width), (NULL));
    
  



gst_directsound_src_unprepare (GstAudioSrc * asrc) 
{
  
  
  
      /* Resets */ 
      GST_DEBUG ("unpreparing directsoundsrc");
  
  
      /* Stop capturing */ 
      hRes = IDirectSoundCaptureBuffer_Stop (dsoundsrc->pDSBSecondary);
  
      /* Release buffer  */ 
      hRes = IDirectSoundCaptureBuffer_Release (dsoundsrc->pDSBSecondary);
  



/* 
return number of readed bytes */ 
static guint 
gst_directsound_src_read (GstAudioSrc * asrc, gpointer data, guint length) 
{
  
  
  
  
  
  
  
  
  
  
  
  
  
      /* Get current buffer status */ 
      hRes =
      IDirectSoundCaptureBuffer_GetStatus (dsoundsrc->pDSBSecondary,
      
  
      /* Starting capturing if not allready */ 
      if (!(dwStatus & DSCBSTATUS_CAPTURING)) {
    
        IDirectSoundCaptureBuffer_Start (dsoundsrc->pDSBSecondary,
        
    
        //    Sleep (dsoundsrc->latency_time/1000);
        GST_DEBUG ("capture started");
  
  
      //  calculate_buffersize:
      while (length > dwBufferSize) {
    
    
        
        
    
        /* calculate the buffer */ 
        if (dwCurrentCaptureCursor < dsoundsrc->current_circular_offset) {
      
          (dsoundsrc->current_circular_offset - 
    
      
          
    
  
  
      /* Lock the buffer */ 
      hRes =
      IDirectSoundCaptureBuffer_Lock (dsoundsrc->pDSBSecondary,
      
      
  
      /* Copy buffer data to another buffer */ 
      if (hRes == DS_OK) {
    
  
  
      /* ...and if something is in another buffer */ 
      if (pLockedBuffer2 != NULL) {
    
  
  
  
  
      
  
  
      /* return length (readed data size in bytes) */ 
      return length;



gst_directsound_src_delay (GstAudioSrc * asrc) 
{
  
  
  
  
  
  
  
  
      /* evaluate the number of samples in queue in the circular buffer */ 
      hRes =
      
      
  
      /* FIXME: Check is this calculated right */ 
      if (hRes == S_OK) {
    
      
          
          
    
      
          
    
    
  
  



gst_directsound_src_reset (GstAudioSrc * asrc) 
{
  
  
  
  
  
  
#if 0
      IDirectSoundCaptureBuffer_Stop (dsoundsrc->pDSBSecondary);
  
#endif /* 
      
  
    
        /*stop capturing */ 
        HRESULT hRes =
        IDirectSoundCaptureBuffer_Stop (dsoundsrc->pDSBSecondary);
    
        /*reset position */ 
        /*    hRes = IDirectSoundCaptureBuffer_SetCurrentPosition (dsoundsrc->pDSBSecondary, 0); */ 
        
        /*reset the buffer */ 
        hRes =
        IDirectSoundCaptureBuffer_Lock (dsoundsrc->pDSBSecondary,
        
        
    
      
      
          
          pLockedBuffer, 
    
    
  
  



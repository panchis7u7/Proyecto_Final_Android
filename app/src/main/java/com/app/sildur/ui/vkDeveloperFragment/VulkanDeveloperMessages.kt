package com.app.sildur.ui.vkDeveloperFragment

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import com.app.sildur.R
import com.app.sildur.ui.viewModels.VulkanSharedDeveloperMessageViewModel
import kotlinx.android.synthetic.main.vkdeveloper_fragment.*

class VkDeveloperFragment : Fragment() {

    //Scope the ViewMode to the mainactivity.
    private val vkSharedMessageViewModel: VulkanSharedDeveloperMessageViewModel by activityViewModels()

    private var param1: String? = null
    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View? {
        //devViewModel = ViewModelProvider(this).get(VkDeveloperViewModel::class.java)
        return inflater.inflate(R.layout.vkdeveloper_fragment, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        val model = ViewModelProvider(requireActivity()).get(VulkanSharedDeveloperMessageViewModel::class.java)
        vkSharedMessageViewModel.m_extensions.observe(viewLifecycleOwner, Observer { item ->
            tvVulkanExtensions.setText(item)
        })
    }
}
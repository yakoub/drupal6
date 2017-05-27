var NodeBlocks = {};

(function($){
  Drupal.behaviors.node_blocks = {
    attach: function(settings, context) {
      NodeBlocks.setUp();

      $('form .block-form-handle').click(function(event){
        NodeBlocks.block = $(this).siblings('input[type="hidden"]');
        NodeBlocks.handle = $(this);
        NodeBlocks.showForm(event.clientX, event.clientY);
      });

      $('form fieldset.block-form select[name="block_modules"]').change(function() {
        var index = $(this).val();
        var module = this.item(index).label;
        NodeBlocks.updateDeltas(module);
      });

      $('form fieldset.block-form .block-save').click(function(event){
        NodeBlocks.saveForm();
      });

      $('form fieldset.block-form .block-cancel').click(function(event){
        NodeBlocks.cancelForm();
      });
    }
  }
})(jQuery);

NodeBlocks.setUp = function() {
  this.form = jQuery('form fieldset.block-form');
  this.deltas = this.form.find('select[name="block_deltas"]').get(0);
  this.blocks = Drupal.settings.node_blocks;
};

NodeBlocks.showForm = function(Xcoord, Ycoord) {
  this.form.css('display', 'block');
  this.form.css('top', Ycoord);
  this.form.css('left', Xcoord);
};

NodeBlocks.saveForm = function() {
  var bid = jQuery(this.deltas).val();
  var title = bid ? jQuery(this.deltas).find('option:selected').text() : Drupal.t('Add block');
  this.block.val(bid ? bid : '');
  this.handle.text(title);
  this.closeForm();
};

NodeBlocks.closeForm = function() {
  var bound = 0;
  while (this.deltas.item(0) != null && bound++ < 100) {
    this.deltas.remove(0);
  }
  this.form.css('display', 'none');
};

NodeBlocks.cancelForm = NodeBlocks.closeForm;


NodeBlocks.updateDeltas = function(module) {
  var bound = 0;
  while (this.deltas.item(0) != null && bound++ < 100) {
    this.deltas.remove(0);
  }

  if (module in this.blocks) {
    var deltas = this.blocks[module];
    for (info in deltas) {
      var option = document.createElement('option');
      option.value = info;
      option.text = deltas[info];
      this.deltas.add(option);
    }
  }
};

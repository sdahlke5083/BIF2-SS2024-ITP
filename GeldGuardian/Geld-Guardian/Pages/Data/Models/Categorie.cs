using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;

namespace Geld_Guardian.Pages.Data.Models
{
    [PrimaryKey("CategorieId")]
    public class Categorie
    {
        public int CategorieId { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        // one to many relationship with BillItem and Bill
        public ICollection<BillItem> BillItems { get; set; }
        public ICollection<Bill> Bills { get; set; }

        public override string ToString()
        {
            return Name;
        }
    }
}
